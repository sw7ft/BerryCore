/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_pageresizebehavior_h
#define cascades_pageresizebehavior_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

/*!
 * 
 * @brief The different ways that a @c Page can be resized when the available screen space is affected by external
 * components (for example, when the keyboard appears).
 *
 * @xmlonly
 * <apigrouping group="User interface/Application structure"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT PageResizeBehavior {
    Q_GADGET
    Q_ENUMS (Type)
public:
    /*!
     * @brief The @c Page resize methods.
     *
     * @since BlackBerry 10.0.0
     */
  enum Type {
    /*! @brief The @c Page keeps its boundaries and can be hidden behind the external components on the screen.
     *
     * @since BlackBerry 10.0.0
     */
    None, 
    /*! @brief The boundaries for the @c Page are set to fit the available screen space left over by the external component.
     *
     * @since BlackBerry 10.0.0
     */
    Resize
  };
/*! @cond PRIVATE */
private:
    PageResizeBehavior();
    ~PageResizeBehavior();
/*! @endcond */
};

} // namespace bb::cascades
}

#endif // cascades_pageresizebehavior_h

