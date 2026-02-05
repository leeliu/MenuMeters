//
//  MenuMeterMemTopProcesses.m
//
//  Reader object for top memory using process list
//  Uses /usr/bin/top (setuid root + com.apple.system-task-ports.read) which
//  reports memory values matching Activity Monitor for ALL processes.
//

#import "MenuMeterMemTopProcesses.h"
#import <libproc.h>

NSString* const kMemProcessPIDKey       = @"pid";
NSString* const kMemProcessNameKey      = @"processName";
NSString* const kMemProcessMemBytesKey  = @"memBytes";

@implementation MenuMeterMemTopProcesses
{
    NSArray *processes;
    NSTimer *refreshTimer;
    BOOL running;
}

- (void)startUpdateProcessList {
    running = YES;
    processes = nil;
    [self refreshProcessList];
    refreshTimer = [NSTimer timerWithTimeInterval:2.0
                                           target:self
                                         selector:@selector(refreshProcessList)
                                         userInfo:nil
                                          repeats:YES];
    [[NSRunLoop mainRunLoop] addTimer:refreshTimer forMode:NSRunLoopCommonModes];
}

- (void)stopUpdateProcessList {
    running = NO;
    [refreshTimer invalidate];
    refreshTimer = nil;
}

- (void)refreshProcessList {
    if (!running) return;

    NSTask *topTask = [NSTask new];
    topTask.launchPath = @"/usr/bin/top";
    topTask.arguments = @[@"-l", @"1", @"-o", @"mem", @"-stats", @"pid,mem,command", @"-n", @"15", @"-s", @"0"];
    NSPipe *topPipe = [NSPipe pipe];
    topTask.standardOutput = topPipe;
    topTask.standardError = [NSPipe pipe];
    @try {
        [topTask launch];
    } @catch (NSException *e) {
        return;
    }
    NSData *data = [[topPipe fileHandleForReading] readDataToEndOfFile];
    [topTask waitUntilExit];

    NSString *output = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    if (!output) return;

    NSMutableArray *list = [NSMutableArray array];
    for (NSString *line in [output componentsSeparatedByString:@"\n"]) {
        NSString *trimmed = [line stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
        if (trimmed.length == 0) continue;

        // Process lines start with a digit (PID); skip header/summary lines
        unichar firstChar = [trimmed characterAtIndex:0];
        if (firstChar < '0' || firstChar > '9') continue;

        // Parse: PID  MEM  COMMAND
        NSArray *parts = [trimmed componentsSeparatedByString:@" "];
        NSMutableArray *tokens = [NSMutableArray array];
        for (NSString *p in parts) {
            if (p.length > 0) [tokens addObject:p];
        }
        if (tokens.count < 3) continue;

        pid_t pid = [tokens[0] intValue];
        if (pid <= 0) continue;

        // Parse memory value (e.g. "637M", "1024M+", "2G", "123K")
        NSString *memField = tokens[1];
        uint64_t memBytes = [self parseMemField:memField];
        if (memBytes < 1024 * 1024) continue; // Skip < 1MB

        // Get full process name via proc_name (top truncates names)
        NSString *name = nil;
        char procName[256] = {0};
        proc_name(pid, procName, sizeof(procName));
        if (procName[0] != '\0') {
            name = [NSString stringWithUTF8String:procName];
        } else {
            // Fallback: try proc_pidpath for basename
            char path[PROC_PIDPATHINFO_MAXSIZE] = {0};
            if (proc_pidpath(pid, path, sizeof(path)) > 0) {
                NSString *fullPath = [NSString stringWithUTF8String:path];
                name = [fullPath lastPathComponent];
            }
        }
        if (!name || name.length == 0) {
            // Last resort: use the truncated name from top
            NSArray *nameParts = [tokens subarrayWithRange:NSMakeRange(2, tokens.count - 2)];
            name = [nameParts componentsJoinedByString:@" "];
        }
        if (name.length == 0) continue;

        [list addObject:@{
            kMemProcessPIDKey: @(pid),
            kMemProcessNameKey: name,
            kMemProcessMemBytesKey: @(memBytes)
        }];
    }

    processes = list;
}

- (uint64_t)parseMemField:(NSString *)field {
    if (field.length == 0) return 0;

    // Strip trailing +/- (compression indicators)
    NSString *clean = field;
    unichar last = [clean characterAtIndex:clean.length - 1];
    if (last == '+' || last == '-') {
        clean = [clean substringToIndex:clean.length - 1];
    }
    if (clean.length == 0) return 0;

    last = [clean characterAtIndex:clean.length - 1];
    double multiplier = 1.0;
    if (last == 'K' || last == 'k') {
        multiplier = 1024.0;
        clean = [clean substringToIndex:clean.length - 1];
    } else if (last == 'M' || last == 'm') {
        multiplier = 1048576.0;
        clean = [clean substringToIndex:clean.length - 1];
    } else if (last == 'G' || last == 'g') {
        multiplier = 1073741824.0;
        clean = [clean substringToIndex:clean.length - 1];
    } else if (last == 'B' || last == 'b') {
        multiplier = 1.0;
        clean = [clean substringToIndex:clean.length - 1];
    }

    return (uint64_t)([clean doubleValue] * multiplier);
}

- (NSArray *)runningProcessesByMemUsage:(NSUInteger)maxItem {
    if (!processes) return @[];
    return [processes subarrayWithRange:NSMakeRange(0, MIN(maxItem, processes.count))];
}

@end
