/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef bb_cascades_abstracttextstylerule_h
#define bb_cascades_abstracttextstylerule_h

#include <bb/cascades/core/baseobject.h>

namespace bb {
namespace cascades {

class AbstractTextStyleRulePrivate;

/*!
 * @brief The base class for all text style rules.
 *
 * The @c TextStyleDefinition::rules property manages the list of text style rules
 * that are applied to a corresponding text style.
 *
 * @see @c TextStyleDefinition::rules, @c FontFaceRule
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BBCASCADES_EXPORT AbstractTextStyleRule : public BaseObject
{
    Q_OBJECT

protected:
    /*! @cond PRIVATE */
    AbstractTextStyleRule(AbstractTextStyleRulePrivate &_d_ptr, QObject *pParent = 0);
    ~AbstractTextStyleRule();
    /*! @endcond */

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(AbstractTextStyleRule)
    Q_DISABLE_COPY(AbstractTextStyleRule)
    /*! @endcond */
};

} // namespace cascades
} // namespace bb

/*! @cond PRIVATE */
QML_DECLARE_INTERFACE(bb::cascades::AbstractTextStyleRulePrivate)
/*! @endcond */

#endif // bb_cascades_abstracttextstylerule_h
