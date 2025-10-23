/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef bb_cascades_abstracta11yspecialization_h
#define bb_cascades_abstracta11yspecialization_h

#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/UIObject>

namespace bb
{
namespace cascades
{

class AbstractA11ySpecializationPrivate;

/*!
 * @brief Class defining an abstract accessibility specialization.
 *
 * @xmlonly
 *     <apigrouping group="User interface/Accessibility"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BBCASCADES_EXPORT AbstractA11ySpecialization : public UIObject {
    Q_OBJECT

public:

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~AbstractA11ySpecialization();

protected:
    /*! @cond PRIVATE */
    explicit AbstractA11ySpecialization(AbstractA11ySpecializationPrivate &_d_ptr, UIObject *parent = 0);
    /*! @endcond */

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(AbstractA11ySpecialization)
    Q_DISABLE_COPY(AbstractA11ySpecialization)
    /*! @endcond */

};

}
}

QML_DECLARE_TYPE(bb::cascades::AbstractA11ySpecialization)

#endif // bb_cascades_abstracta11yspecialization_h
