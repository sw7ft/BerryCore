/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef cascades_listviewsticktoedgepolicy_h
#define cascades_listviewsticktoedgepolicy_h

#include <bb/cascades/bbcascades_global.h>
#include <QtDeclarative/QtDeclarative>

namespace bb {
    namespace cascades {

    /*!
     * @brief Represents the different policies of maintaining edge positions for the @c ListView.
     *
     * @xmlonly
     * <apigrouping group="User interface/List"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.1.0
     */
    class BBCASCADES_EXPORT ListViewStickToEdgePolicy
    {
        Q_GADGET
        Q_ENUMS(Type)
    public:
        /*!
         * @brief The enumeration of @c ListView stick-to-edge policies.
         *
         * @since BlackBerry 10.1.0
         */
        enum Type {
            /*! 
             * @brief The framework decides the behavior.
             *
             * @since BlackBerry 10.1.0
             */
            Default = 0x0,
            /*! 
             * @brief No particular stick-to-edge behavior.
             *
             * @since BlackBerry 10.1.0
             */
            None = 0x1,
            /*! 
             * @brief The @c ListView will try to maintain the beginning of the list in view.
             *
             * @since BlackBerry 10.1.0
             */
            Beginning = 0x2,
            /*! 
             * @brief The @c ListView will try to maintain the end of the list in view.
             *
             * @since BlackBerry 10.1.0
             */
            End = 0x3,
            /*! 
             * @brief The @c ListView will try to maintain both the beginning and the end of 
             * the list in view. When there is a conflict, it will stick to the beginning.
             *
             * @since BlackBerry 10.1.0
             *  
             */
            BeginningThenEnd = 0x4,
            /*! 
             * @brief The @c ListView will try to maintain both the beginning and the end of
             * the list in view. When there is a conflict, it will stick to the end.
             *
             * @since BlackBerry 10.1.0
             *  
             */
            EndThenBeginning = 0x5
        };
    private:
        ListViewStickToEdgePolicy();
        ~ListViewStickToEdgePolicy();
    };


    } // cascades
} // bb

#endif // cascades_listviewsticktoedgepolicy_h
