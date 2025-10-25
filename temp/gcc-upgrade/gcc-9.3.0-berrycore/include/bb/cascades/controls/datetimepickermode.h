/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_datetimepickermode_h
#define cascades_datetimepickermode_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

   /*!
    * @brief Represents the modes used for the @c DateTimePicker.
    *
    * Use the @c %DateTimePickerMode::Type enum values to set a specific mode for the @c %DateTimePicker.
    * The default mode is @c DateTimePickerMode::Date.
    *
    * Here's an example of how to specify the @c %DateTimePickerMode, in QML.
    * @code
    * DateTimePicker {
    *     mode: DateTimePickerMode.Time
    * }
    * @endcode
    *
    * Here's an example of setting the mode in C++:
    * @code
    * DateTimePicker* dateTimePicker::create()
    *         .mode(DateTimePickerMode::Time);
    * @endcode
    *
    * It's also possible to change the mode anytime during runtime:
    * @code
    * dateTimePicker->setMode(DateTimePickerMode::Date);
    * @endcode
    *
    * @xmlonly
    * <apigrouping group="User interface/Core controls"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT DateTimePickerMode {
        Q_GADGET
        Q_ENUMS (Type)
    
    public:

        /*!
        * @brief Different modes available for the @c DateTimePicker:
         *
         * @since BlackBerry 10.0.0
        */
        enum Type {
            /*!
             * @brief Shows two columns with hours and minutes.
             *
             * @since BlackBerry 10.0.0
             */
            Time = 0,
            /*! 
             * @brief Shows three columns with day, month and year (default).
             *
             * @since BlackBerry 10.0.0
             */
            Date,
            /*!
             * @brief Shows three columns with day, hours and minutes.
             *
             * @since BlackBerry 10.0.0
             */
            DateTime,
            /*!
             * @brief Shows three columns with hours, minutes and seconds.
             *
             * @since BlackBerry 10.0.0
             */
            Timer
        };
    
    private:

      DateTimePickerMode();
      virtual ~DateTimePickerMode();
    
    };
}
}

#endif // cascades_datetimepickermode_h
