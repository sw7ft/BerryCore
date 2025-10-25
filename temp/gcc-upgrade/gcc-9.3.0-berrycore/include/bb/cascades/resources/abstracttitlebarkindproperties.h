/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_abstracttitlebarkindproperties_h
#define cascades_abstracttitlebarkindproperties_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>

namespace bb {
    namespace cascades {

    class AbstractTitleBarKindPropertiesPrivate;

    /*!
     * 
     * @brief An abstract base class inherited by all title bar kind properties classes.
     *
     * @see @c FreeFormTitleBarKindProperties
     * 
     * @xmlonly
     * <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT AbstractTitleBarKindProperties : public UIObject {
    private:
        Q_OBJECT

    public:
        virtual ~AbstractTitleBarKindProperties();

    protected:
        /*! @cond PRIVATE */
        AbstractTitleBarKindProperties(AbstractTitleBarKindPropertiesPrivate &_d_ptr);

    private:
        Q_DECLARE_PRIVATE(AbstractTitleBarKindProperties)
        Q_DISABLE_COPY(AbstractTitleBarKindProperties)
       /*! @endcond */
    };
}
}


QML_DECLARE_TYPE(bb::cascades::AbstractTitleBarKindProperties)


#endif // cascades_abstracttitlebarkindproperties_h
