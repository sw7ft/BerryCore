/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_paneproperties_h
#define cascades_paneproperties_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>

namespace bb {
    namespace cascades {

    class PanePropertiesPrivate;

    /*!
     * 
     * @brief An abstract base class inherited by all pane properties classes.
     * 
     * Any class deriving from this class can be set on an @c AbstractPane to define data for the parent class
     * (for example, @c NavigationPane).
     *     
     *
     * @xmlonly
     * <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT PaneProperties : public UIObject {
    private:
        Q_OBJECT

    public:
        virtual ~PaneProperties();

    protected:
        /*! @cond PRIVATE */
        PaneProperties(PanePropertiesPrivate &_d_ptr);

    private:
        Q_DECLARE_PRIVATE(PaneProperties)
        Q_DISABLE_COPY(PaneProperties)
       /*! @endcond */
    };
}
}


QML_DECLARE_TYPE(bb::cascades::PaneProperties)


#endif	// cascades_paneproperties_h
