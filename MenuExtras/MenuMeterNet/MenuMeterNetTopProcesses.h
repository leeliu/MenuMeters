//
//  MenuMeterNetTopProcesses.h
//
//  Reader object for top network using process list
//

#import <Cocoa/Cocoa.h>

extern NSString* const kNetProcessPIDKey;
extern NSString* const kNetProcessNameKey;
extern NSString* const kNetProcessBytesInPerSecKey;
extern NSString* const kNetProcessBytesOutPerSecKey;

@interface MenuMeterNetTopProcesses : NSObject

- (NSArray *)runningProcessesByNetUsage:(NSUInteger)maxItem;
- (void)startUpdateProcessList;
- (void)stopUpdateProcessList;

@end
