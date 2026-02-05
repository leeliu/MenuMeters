//
//  MenuMeterMemTopProcesses.h
//
//  Reader object for top memory using process list
//

#import <Cocoa/Cocoa.h>

extern NSString* const kMemProcessPIDKey;
extern NSString* const kMemProcessNameKey;
extern NSString* const kMemProcessMemBytesKey;

@interface MenuMeterMemTopProcesses : NSObject

- (NSArray *)runningProcessesByMemUsage:(NSUInteger)maxItem;
- (void)startUpdateProcessList;
- (void)stopUpdateProcessList;

@end
