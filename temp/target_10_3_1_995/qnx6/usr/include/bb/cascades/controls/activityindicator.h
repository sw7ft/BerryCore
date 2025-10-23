/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_activityindicator_h
#define cascades_activityindicator_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>

namespace bb {
    namespace cascades {

    class ActivityIndicatorPrivate;
    class Container;

    /*!
     * @brief A control that indicates that a process is being completed.
     *
     * @image html activityindicator.png Example of what the activity indicator looks like
     *
     * The activity indicator is useful when the length of time for a particular process cannot
     * accurately be determined, or may take a long time.
     *
     * The activity indicator has three fixed graphics sizes. The size of the indicator and how it is positioned is determined according to the following input:
     * - The activity indicator will choose the largest of its three graphics sizes that fits inside the avaliable space.
     * - If the avaliable space is not exactly the right size the graphics will be centered in the avaliable space. The graphics will never be scaled.
     * - By default, it will not request a larger area than its smallest graphics size from the layout system.
     * - The control will try to respect preferred, min and max sizes if they are set by the user.
     *
     * Explanation of ActivityIndicator states/signals:
     * @code
     * start()     started                       stop()      stopped
     *   |------------|----------------------------|------------|
     *
     *   |----------------running------------------|--stopping--|
     * @endcode
     *
     * Here's an example of a simple activity indicator in QML:
     *
     * @snippet tad/examples/controls/activityindicator/assets/main.qml activityindicator_qml
     *
     * @see ProgressIndicator
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ActivityIndicator : public Control
    {
    private:
        Q_OBJECT

        /*!
         * @brief Indicates whether the activity indicator is running.
         *
         * When @c true, the @c %ActivityIndicator is running, when @c false it
         * is stopped. The signal is emitted as soon as the @c %ActivityIndicator starts to run.
         *
         * Setting the property to @c true starts the animation while @c false stops it.
         *
         * The default value of this property is @c false.
         *
         * @note An @c %ActivityIndicator is created with @c %visible == false and @c %opacity == 0. When an
         * ActivityIndicator is started, Cascades overrides the values, setting @c %visible == true and
         * @c %opacity == 1. When an ActivityIndicator is stopped, Cascades overrides the values again,
         * setting @c %visible == false and @c %opacity ==0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool running READ isRunning WRITE setRunning RESET resetRunning NOTIFY runningChanged FINAL)

    public:
        /*!
         * @brief Constructs a activity indicator with a parent.
         *
         * @param parent The parent container or @c 0. This parameter is optional and will default to @c 0 if not specified.
         * If not @c 0, the ownership of the constructed activity indicator will be transferred to the parent.
         *
         * @since BlackBerry 10.0.0
         */
        explicit ActivityIndicator(Container * parent = 0);
  
        /*!
         * Destructs the activity indicator.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~ActivityIndicator();

        /*!
         * @brief Start animating of the activity indicator.
         *
         * After the start animation is completed, the @c started() signal is emitted. No signal will be 
         * emitted if the activity indicator is already started.
         * This is equivalent to calling @c setRunning(true)
         *
         * @note Cascades maintains the @c visible and @c opacity properties of an @c %ActivityIndicator. An
         * @c %ActivityIndicator becomes visible (@c %opacity == 1) when it is running, and it is not visible
         * (@c %opacity == 0) when it is stopped. As a result, you should not read or set the @c %visible
         * and @c %opacity properties of an @c %ActivityIndicator.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void start();

        /*!
         * @brief Stop animating the activity indicator.
         *
         * After the stop animation is completed, the @c stopped() signal is emitted. No signal will 
         * be emitted if the activity indicator is already stopped.
         * This is for convenience and is equivalent to @c setRunning(false)
         *
         * @note Cascades maintains the @c visible and @c opacity properties of an @c %ActivityIndicator. An
         * @c %ActivityIndicator becomes visible (@c %opacity == 1) when it is running, and it is not visible
         * (@c %opacity == 0) when it is stopped. As a result, you should not read or set the @c %visible
         * and @c %opacity properties of an @c %ActivityIndicator.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void stop();

        /*!
         * @brief Determines if the activity indicator is currently running.
         *
         * The activity indicator is running from the time that @c start() is called until @c stop() is called.
         *
         * @return @c true if the activity indicator is running, False otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isRunning() const;

        /*!
         * @brief Sets the running state.
         *
         * If the state change is successful, the @c runningChanged() signal is emitted.
         *
         * @param running The new state to set. @c true for running, and @c false to stop it.
         *
         * @note Cascades maintains the @c visible and @c opacity properties of an @c %ActivityIndicator. An
         * @c %ActivityIndicator becomes visible (@c %opacity == 1) when it is running, and it is not visible
         * (@c %opacity == 0) when it is stopped. As a result, you should not read or set the @c %visible
         * and @c %opacity properties of an @c %ActivityIndicator.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setRunning(bool running);

        /*!
         * @brief Resets the running state to @c false, which stops the indicator.
         *
         * When called, the @c runningChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetRunning();

    Q_SIGNALS:
        /*!
         * @brief Emitted when the activity indicator is started.
         *
         * The signal will not be emitted until the startup animation of the activity indicator is finished.
         * This signal can be used for example if the application developer wants to delay stopping
         * the indicator so that the full startup animation is always shown.
         * This signal is the equivalent to @c runningChanged(true).
         *
         * @since BlackBerry 10.0.0
         */
        void started();

        /*!
         * @brief Emitted when the activity indicator is stopped.
         *
         * This signal will not be emitted until
         * the stop animation of the activity indicator is finished.
         * This signal can be used if the application developer wants to delay navigation or hide
         * the activity indicator until the stop animation has finished.
         *
         * @since BlackBerry 10.0.0
         */
        void stopped();

        /*!
         * @brief Emitted when the activity indicator is stopping.
         *
         * The signal will be emitted immediately once the stop() function has been called, regardless
         * of whether the indicator has stopped completely.
         * This signal can be useful if the developer wants to perform some sort of action
         * before the activity indicator has stopped completely.
         * This signal is the equivalent to @c runningChanged(false).
         *
         * @since BlackBerry 10.0.0
         */
        void stopping();

        /*!
         * @brief Emitted when the running state has been changed.
         *
         * @c runningChanged(true) is the equivalent to @c started(), while
         * @c runningChanged(false) is the equivalent to @c stopping().
         *
         * @param running The newly set running state
         *
         * @since BlackBerry 10.0.0
         */
        void runningChanged(bool running);

    private:
        Q_DECLARE_PRIVATE(ActivityIndicator)
        Q_DISABLE_COPY(ActivityIndicator)
        
        /*! \cond PRIVATE */
        typedef ActivityIndicator ThisClass;
        typedef Control BaseClass;
        /*! \endcond */

    public:
        /*!
         * @brief A builder that constructs an @c ActivityIndicator. To retrieve the builder, call
         * @c ActivityIndicator::create().
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
        {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node)
            {
            }
        };

        /*!
         * @brief A builder that constructs an @c ActivityIndicator. To retrieve the builder, call
         * @c ActivityIndicator::create().
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, ActivityIndicator>
        {
        public:
            explicit Builder() : TBuilder<Builder, ActivityIndicator>(new ActivityIndicator())
            {
            }
        };

        /*!
         * @brief Creates and returns a builder for constructing an activity indicator.
         *
         * Using the builder to create an activity indicator:
         * @code
         * ActivityIndicator* myIndicator = ActivityIndicator::create();
         * @endcode
         *
         * @return A builder used for constructing an activity indicator.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create()
        {
            return Builder();
        }
    };
}
}

QML_DECLARE_TYPE(bb::cascades::ActivityIndicator)

#endif


