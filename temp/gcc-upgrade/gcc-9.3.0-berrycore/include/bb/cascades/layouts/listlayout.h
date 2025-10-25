/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_listlayout_h
#define cascades_listlayout_h

#include <QtCore/QObject>
#include <QtDeclarative/QtDeclarative>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>


namespace bb {
    namespace cascades {

      class ListLayoutPrivate;

    /*!
     *
     * @brief Abstract base class for list layouts.
     *
     * When a layout is assigned to a @c ListView, it will arrange the list items
     * according to the rules of the particular layout.
     *
     * List layouts include @c StackListLayout, which arranges its children in a stack,
     * @c GridListLayout, which arranges its children in a grid, and @c FlowListLayout
     * which fills rows or columns with as many items as there's room for.
     *
     * @xmlonly
     * <apigrouping group="User interface/Layouts"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ListLayout : public UIObject {
    private:
        Q_OBJECT

    public:
        virtual ~ListLayout();

    protected:
        /*! @cond PRIVATE */
        ListLayout(ListLayoutPrivate &_d_ptr);
        /*! \endcond */

    private:
        Q_DECLARE_PRIVATE(ListLayout)
        Q_DISABLE_COPY(ListLayout)
    }; // class ListLayout
    } // namespace bb::cascades
} // namespace bb

QML_DECLARE_TYPE(bb::cascades::ListLayout)

#endif	// cascades_listlayout_h
