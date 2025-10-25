/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef cascades_a11ycomponentactivationtype_h
#define cascades_a11ycomponentactivationtype_h

#include <QObject>
#include <bb/cascades/bbcascades_global.h>

namespace bb
{
    namespace cascades
    {

    /*!
     * @brief Provides an enumeration describing the different types of activations that can be performed through accessibility.
     *
     * @see @c ComponentA11ySpecialization
     * @see @c A11yComponentActivationEvent::type
     *
     * @xmlonly
     *     <apigrouping group="User interface/Accessibility"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.2.0
     */
    class BBCASCADES_EXPORT A11yComponentActivationType {
        Q_GADGET
        Q_ENUMS(Type)

    public:
        /*!
        * @brief The types of activations that can be performed.
        *
        * @since BlackBerry 10.2.0
        */
        enum Type {
            /*!
            * @brief Do the default action (if at all).
            *
            * @since BlackBerry 10.2.0
            */
            Default = 0,

            /*!
            * @brief A tap.
            *
            * @since BlackBerry 10.2.0
            */
            Tap = 1,

            /*!
            * @brief A long press.
            *
            * @since BlackBerry 10.2.0
            */
            LongPress = 2,

            /*!
            * @brief A swipe up.
            *
            * @since BlackBerry 10.2.0
            */
            SwipeUp = 3,

            /*!
            * @brief A swipe left.
            *
            * @since BlackBerry 10.2.0
            */
            SwipeLeft = 4,

            /*!
            * @brief A swipe down.
            *
            * @since BlackBerry 10.2.0
            */
            SwipeDown = 5,

            /*!
            * @brief A swipe right.
            *
            * @since BlackBerry 10.2.0
            */
            SwipeRight = 6,

            /*!
            * @brief A double tap.
            *
            * @since BlackBerry 10.2.0
            */
            DoubleTap = 7,

            /*!
            * @brief A touch release event.
            *
            * @since BlackBerry 10.2.0
            */
            Release = 8,

            /*!
            * @brief A request to scroll one page up.
            *
            * If the component is scrollable or pannable,
            * this activate should cause the component to scroll
            * up a full page. If the component is not
            * scrollable, the activate event should be
            * propagated to the parent control so that it
            * can handle the request.
            *
            * The action should emulate what would happen
            * if the user hit a "PAGE UP" key on a computer
            * keyboard, or the "u" shortcut key on the
            * device.
            *
            * @since BlackBerry 10.2.0
            */
            PageUp = 9,

            /*!
            * @brief A request to scroll one page down.
            *
            * If the component is scrollable or pannable,
            * this activate should cause the component to scroll
            * down a full page. If the component is not
            * scrollable, the activate event should be
            * propagated to the parent control so that it
            * can handle the request.
            *
            * The action should emulate what would happen
            * if the user hit a "PAGE DN" key on a computer
            * keyboard, or the "d" shortcut key on the
            * device.
            *
            * @since BlackBerry 10.2.0
            */
            PageDown = 10,

            /*!
            * @brief A request to scroll one page left.
            *
            * If the component is scrollable or pannable,
            * this activate should cause the component to scroll
            * left a full page. If the component is not
            * scrollable, the activate event should be
            * propagated to the parent control so that it
            * can handle the request.
            *
            * @since BlackBerry 10.2.0
            */
            PageLeft = 11,

            /*!
            * @brief A request to scroll one page right.
            *
            * If the component is scrollable or pannable,
            * this activate should cause the component to scroll
            * right a full page. If the component is not
            * scrollable, the activate event should be
            * propagated to the parent control so that it
            * can handle the request.
            *
            * @since BlackBerry 10.2.0
            */
            PageRight = 12,

            /*!
            * @brief A request to scroll to the top.
            *
            * If the component is scrollable
            * this activate should cause the component to scroll
            * to the top of its list. If the component is not
            * scrollable, the activate event should be
            * propagated to the parent control so that it
            * can handle the request.
            *
            * The action should emulate what would happen
            * if the user hit the "HOME" key on a computer
            * keyboard, or the "t" shortcut key on the
            * device.
            *
            * @since BlackBerry 10.2.0
            */
            Home = 13,

            /*!
            * @brief A request to scroll to the bottom.
            *
            * If the component is scrollable
            * this activate should cause the component to scroll
            * to the bottom of its list. If the component is not
            * scrollable, the activate event should be
            * propagated to the parent control so that it
            * can handle the request.
            *
            * The action should emulate what would happen
            * if the user hit the "END" key on a computer
            * keyboard, or the "b" shortcut key on the
            * device.
            *
            * @since BlackBerry 10.2.0
            */
            End = 14,

            /*!
            * @brief A request to scroll to the next section.
            *
            * If the component is scrollable
            * this activate should cause the component to scroll
            * to the next section. For example in a
            * list, it should take the user to the next list header.
            *
            * The action should emulate what would happen
            * if the user hit the "n" shortcut key on the
            * device.
            *
            * @since BlackBerry 10.2.0
            */
            Forward = 15,

            /*!
            * @brief A request to scroll to the previous section.
            *
            * If the component is scrollable
            * this activate should cause the component to scroll
            * to the previous section. For example in a
            * list, it should take the user to the previous list header.
            *
            * The action should emulate what would happen
            * if the user hit the "p" shortcut key on the
            * device.
            *
            * @since BlackBerry 10.2.0
            */
            Backward = 16,

            /*!
            * @brief A request to zoom in.
            *
            * If the component is zoomable or scalable
            * this activate should cause a zoom in on the
            * component.
            *
            * The action should emulate what would happen
            * if the user hit the "i" shortcut key on the
            * device.
            *
            * @since BlackBerry 10.2.0
            */
            ZoomIn = 17,

            /*!
            * @brief A request to zoom out.
            *
            * If the component is zoomable or scalable
            * this activate should cause a zoom out on the
            * component.
            *
            * The action should emulate what would happen
            * if the user hit the "o" shortcut key on the
            * device.
            *
            * @since BlackBerry 10.2.0
            */
            ZoomOut = 18
        };

    private:
        /*! @cond PRIVATE */
        A11yComponentActivationType();
        ~A11yComponentActivationType();
        /*! @endcond */
    };
    }
}

#endif // cascades_a11ycomponentactivationtype_h

