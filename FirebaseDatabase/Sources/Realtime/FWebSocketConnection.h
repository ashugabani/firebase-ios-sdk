/*
 * Copyright 2017 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import "FirebaseDatabase/Sources/Utilities/FUtilities.h"
#import <Foundation/Foundation.h>

@protocol FWebSocketDelegate;

@interface FWebSocketConnection : NSObject <NSURLSessionWebSocketDelegate>

@property(nonatomic, weak) id<FWebSocketDelegate> delegate;

- (instancetype)initWith:(FRepoInfo *)repoInfo
                andQueue:(dispatch_queue_t)queue
             googleAppID:(NSString *)googleAppID
           lastSessionID:(NSString *)lastSessionID
           appCheckToken:(NSString *)appCheckToken;

- (void)open;
- (void)close;
- (void)start;
- (void)send:(NSDictionary *)dictionary;

@end

@protocol FWebSocketDelegate <NSObject>

- (void)onMessage:(FWebSocketConnection *)fwebSocket
      withMessage:(NSDictionary *)message;
- (void)onDisconnect:(FWebSocketConnection *)fwebSocket
    wasEverConnected:(BOOL)everConnected;

@end
