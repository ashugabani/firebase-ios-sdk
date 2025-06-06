/*
 * Copyright 2019 Google
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

#import <Foundation/Foundation.h>

@class FIRApp;
@class FIRInstallationsAuthTokenResult;

NS_ASSUME_NONNULL_BEGIN

/** A notification with this name is sent each time an installation is created or deleted. */
// clang-format off
// clang-format12 merges the next two lines.
FOUNDATION_EXPORT const NSNotificationName FIRInstallationIDDidChangeNotification
    NS_SWIFT_NAME(InstallationIDDidChange);
/** `userInfo` key for the `FirebaseApp.name` in `InstallationIDDidChangeNotification`. */
FOUNDATION_EXPORT NSString *const kFIRInstallationIDDidChangeNotificationAppNameKey
    NS_SWIFT_NAME(InstallationIDDidChangeAppNameKey);
// clang-format on

/**
 * An installation ID handler block.
 * @param identifier The installation ID string if exists or `nil` otherwise.
 * @param error The error when `identifier == nil` or `nil` otherwise.
 */
typedef void (^FIRInstallationsIDHandler)(NSString *__nullable identifier,
                                          NSError *__nullable error)
    NS_SWIFT_UNAVAILABLE("Use Swift's closure syntax instead.");

/**
 * An authorization token handler block.
 * @param tokenResult An instance of `InstallationsAuthTokenResult` in case of success or `nil`
 * otherwise.
 * @param error The error when `tokenResult == nil` or `nil` otherwise.
 */
typedef void (^FIRInstallationsTokenHandler)(
    FIRInstallationsAuthTokenResult *__nullable tokenResult, NSError *__nullable error)
    NS_SWIFT_UNAVAILABLE("Use Swift's closure syntax instead.");

/**
 * The class provides API for Firebase Installations.
 * Each configured `FirebaseApp` has a corresponding single instance of `Installations`.
 * An instance of the class provides access to the installation info for the `FirebaseApp` as well
 * as the ability to delete it. A Firebase Installation is unique by `FirebaseApp.name` and
 * `FirebaseApp.options.googleAppID` .
 */
NS_SWIFT_NAME(Installations) NS_SWIFT_SENDABLE @interface FIRInstallations : NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
 * Returns a default instance of `Installations`.
 * @return An instance of `Installations` for `FirebaseApp.defaultApp().
 * @throw Throws an exception if the default app is not configured yet or required  `FirebaseApp`
 * options are missing.
 */
+ (FIRInstallations *)installations NS_SWIFT_NAME(installations());

/**
 * Returns an instance of `Installations` for an application.
 * @param application A configured `FirebaseApp` instance.
 * @return An instance of `Installations` corresponding to the passed application.
 * @throw Throws an exception if required `FirebaseApp` options are missing.
 */
+ (FIRInstallations *)installationsWithApp:(FIRApp *)application NS_SWIFT_NAME(installations(app:));

/**
 * The method creates or retrieves an installation ID. The installation ID is a stable identifier
 * that uniquely identifies the app instance. NOTE: If the application already has an existing
 * FirebaseInstanceID then the InstanceID identifier will be used.
 * @param completion A completion handler which is invoked when the operation completes.
 */
- (void)installationIDWithCompletion:(void (^)(NSString *__nullable identifier,
                                               NSError *__nullable error))completion;

/**
 * Retrieves (locally if it exists or from the server) a valid installation auth token. An existing
 * token may be invalidated or expired, so it is recommended to fetch the installation auth token
 * before each server request. The method does the same as
 * `Installations.authToken(forcingRefresh:completion:)` with forcing refresh `false`.
 * @param completion A completion handler which is invoked when the operation completes.
 */
- (void)authTokenWithCompletion:(void (^)(FIRInstallationsAuthTokenResult *__nullable tokenResult,
                                          NSError *__nullable error))completion;

/**
 * Retrieves (locally or from the server depending on `forceRefresh` value) a valid installation
 * auth token. An existing token may be invalidated or expire, so it is recommended to fetch the
 * installation auth token before each server request. This method should be used with `forceRefresh
 * == true` when e.g. a request with the previously fetched installation auth token failed with "Not
 * Authorized" error.
 * @param forceRefresh If `true` then the locally cached installation auth token will be ignored and
 * a new one will be requested from the server. If `false`, then the locally cached installation
 * auth token will be returned if exists and has not expired yet.
 * @param completion  A completion handler which is invoked when the operation completes. See
 * `InstallationsTokenHandler` for additional details.
 */
- (void)authTokenForcingRefresh:(BOOL)forceRefresh
                     completion:(void (^)(FIRInstallationsAuthTokenResult *__nullable tokenResult,
                                          NSError *__nullable error))completion;

/**
 * Deletes all the installation data including the unique identifier, auth tokens and
 * all related data on the server side. A network connection is required for the method to
 * succeed. If fails, the existing installation data remains untouched.
 * @param completion A completion handler which is invoked when the operation completes. `error ==
 * nil` indicates success.
 */
- (void)deleteWithCompletion:(void (^)(NSError *__nullable error))completion;

@end

NS_ASSUME_NONNULL_END
