import { EnhancedEventEmitter } from './EnhancedEventEmitter';
import { Worker, WorkerSettings } from './Worker';
import * as types from './types';
/**
 * Expose all types.
 */
export { types };
/**
 * Expose mediasoup version.
 */
export declare const version = "1.0.0";
export type ObserverEvents = {
    newworker: [Worker];
};
declare const observer: EnhancedEventEmitter<ObserverEvents>;
/**
 * Observer.
 */
export { observer };
/**
 * Create a Worker.
 */
export declare function createWorker({ logLevel, logTags, rtcMinPort, rtcMaxPort, dtlsCertificateFile, dtlsPrivateKeyFile, appData }?: WorkerSettings): Promise<Worker>;
//# sourceMappingURL=index.d.ts.map