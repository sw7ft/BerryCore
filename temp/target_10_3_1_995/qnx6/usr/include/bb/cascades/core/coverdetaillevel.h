/*!
 * Copyright (C) 2012 - 2014 BlackBerry Limited. All rights reserved.
 */

#ifndef cascades_coverdetaillevel_h
#define cascades_coverdetaillevel_h

#include <QObject>
#include <bb/cascades/bbcascades_global.h>

namespace bb {
    namespace cascades {

    /*!
     *
     * @brief A class representing cover detail level options.
     *
     * By default, a cover created for use in a @c MultiCover has the
     * detail level Default, which currently gets transleted to High upon usage.
     * The detail level controls which cover will get displayed on the screen
     * when the application is minimized. A High detail level will be used
     * when a large cover is displayed, and a Medium one will be used whe a
     * smaller cover is displayed.
     *
     * @xmlonly
     * <apigrouping group="User interface/Core"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.0
     */
    class BBCASCADES_EXPORT CoverDetailLevel {
        Q_GADGET
        Q_ENUMS(Type)

    public:
        /*!
         * @brief Specifies the cover detail level.
         *
         * @since BlackBerry 10.3.0
         */
        enum Type {
            /*! @brief The default value, which is typically the same as @c High.
             *
             * @since BlackBerry 10.3.0
             */
            Default = 0,
            /*! @brief Specifies that the detail level should be High.
             *
             * @since BlackBerry 10.3.0
             */
            High,
            /*! @brief Specifies that the detail level should be Medium.
             *
             * @since BlackBerry 10.3.0
             */
            Medium
          };

    private:
      /*! @cond PRIVATE */
      CoverDetailLevel();
      ~CoverDetailLevel();
      /*! @endcond */
    };
    }
}

#endif //cascades_coverdetaillevel_h
