/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_ABSTRACTBPSEVENTHANDLER_HPP
#define BB_CORE_ABSTRACTBPSEVENTHANDLER_HPP

#include <bb/Global>

struct bps_event_t;
class QThread;

namespace bb
{

/*!
 * @headerfile AbstractBpsEventHandler.hpp <bb/AbstractBpsEventHandler>
 *
 * @brief Sub-class @c AbstractBpsEventHandler and implement @c event() to process raw BPS events.
 *
 * The @c %AbstractBpsEventHandler class is an abstract base class that consumers of BPS events must sub-class to 
 * implement the @c event() method. @c %AbstractBpsEventHandler sub-classes register themselves to receive BPS events 
 * by calling @c subscribe() and providing a value returned by one of the @c xxx_get_domain() BPS functions 
 * (for example, @c clock_get_domain()). Any BPS event that matches this domain will be passed to the handler's 
 * @c event() method when it arrives. Handlers can register for multiple domains by calling @c subscribe() 
 * multiple times. BPS events for each domain are processed on the same thread as the corresponding call to
 * @c subscribe(). Calling @c subscribe() on multiple threads using the same domain will result in events
 * from that domain being received on each of those threads. A thread must have an event loop running in order
 * to receive BPS events.
 *
 * @c %AbstractBpsEventHandler sub-classes are responsible for calling the appropriate function to start the 
 * flow of BPS events (for example, @c clock_request_events()). If you fail to do so and still call @c subscribe(), 
 * no events will ever be delivered to your handler.
 *
 * Note most BPS functions operate on per thread global state and are sensitive to the calling thread. Be 
 * aware that it is not currently possible to call a BPS function from thread A that affects the flow of 
 * events in thread B. Consequently, if an @c %AbstractBpsEventHandler subscribes to events on thread B, make sure you
 * only call BPS functions for it on thread B.
 *
 * Example usage:
 * @snippet libbb/abstractbpseventhandler_example.cpp Creating a subclass of AbstractBpsEventHandler
 * @link libbb/abstractbpseventhandler_example.cpp
 * See full example
 * @endlink
 *
 * @xmlonly
 * <apigrouping group="Platform/Utility"/>
 * <library name="bb"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_CORE_EXPORT AbstractBpsEventHandler
{
public:

    /*!
     * @brief Creates a new @c AbstractBpsEventHandler object.
     *
     * @since BlackBerry 10.0.0
     */
    AbstractBpsEventHandler();
    
    /*!
     * @brief Destroy this instance of the @c AbstractBpsEventHandler.
     *
     * Destroys this @c AbstractBpsEventHandler object and automatically unsubscribes it from all events. To avoid a
     * race condition between unsubscribing and deleting, delete this object on the same thread that it receives 
     * events.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~AbstractBpsEventHandler();

    /*!
     * @brief Called when a BPS event arrives for a subscribed domain.
     *
     * This method is invoked on the @c QThread 
     * that was active when @c subscribe() was called with this domain.
     *
     * @param event The raw BPS event received by the @c QThread.
     *
     * Example usage:
     * @snippet libbb/abstractbpseventhandler_example.cpp Handling the event method
     * @link libbb/abstractbpseventhandler_example.cpp
     * See full example
     * @endlink
     *
     * @since BlackBerry 10.0.0
     */
    virtual void event(bps_event_t *event) = 0;
    /*! @example libbb/abstractbpseventhandler_example.cpp
     * An example showing the usage of the AbstractBpsEventHandler class.
     */
protected:
    
    /*!
     * @brief Register to receive BPS events of the specified domain on the current thread.
     *
     * Register to receive BPS events, which match the provided 
     * domain, that arrive on the specified @c QThread. An instance of @c QAbstractEventDispatcher must exist for the current @c QThread or
     * subscribing will fail. On the main thread, a @c QAbstractEventDispatcher is created when you
     * create your application. On other threads, a @c QAbstractEventDispatcher is not available
     * until @c QThread::exec() is called.
     *
     * @param domain A value returned by one of the @c xxx_get_domain() BPS functions (for example, @c clock_get_domain()).
     *
     * Example usage:
     * @snippet libbb/abstractbpseventhandler_example.cpp Subscribing to a domain
     * @link libbb/abstractbpseventhandler_example.cpp
     * See full example
     * @endlink
     *
     * @since BlackBerry 10.0.0
     */
    void subscribe(int domain);

    /*!
     * @brief Unregister the specified domain from the notifications to be received.
     *
     * Unregister to receive BPS events previously subscribed to using @c subscribe(). To avoid a race 
     * condition between unsubscribing and receiving an event, unsubscribe on the same thread that this object 
     * receives events.
     *
     * @param domain A value returned by one of the @c xxx_get_domain() BPS functions (for example, @c clock_get_domain()).
     *
     * @since BlackBerry 10.0.0
     */
    void unsubscribe(int domain);
};

} // namespace bb

#endif // BB_CORE_ABSTRACTBPSEVENTHANDLER_HPP
