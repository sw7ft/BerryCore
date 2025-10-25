/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef BB_CASCADES_TITLEBAREXPANDABLEAREA_H
#define BB_CASCADES_TITLEBAREXPANDABLEAREA_H

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/BaseObject>

#include <QtDeclarative/QtDeclarative>

#include <bb/cascades/resources/titlebarexpandableareatogglearea.h>
#include <bb/cascades/resources/titlebarexpandableareaindicatorvisibility.h>

namespace bb {
namespace cascades {

class TitleBarExpandableAreaPrivate;
class Control;

/*!
 * 
 * @brief Describes an expandable area, such as @c FreeFormTitleBarProperties.
 * 
 * @xmlonly
 * <apigrouping group="User interface/Application structure"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.1.0
 */
class BBCASCADES_EXPORT TitleBarExpandableArea : public BaseObject
{
    Q_OBJECT

   /*!
    * @brief The content of the expandable area of the @c TitleBar.
    *
    * If the @c expanded property is @c true the control specified by content will be shown.
    *
    * @since BlackBerry 10.1.0
    */
    Q_PROPERTY(bb::cascades::Control* content READ content WRITE setContent RESET resetContent NOTIFY contentChanged FINAL)

   /*!
    * The expanded state. A value of @c true means that the expandable area is shown, @c false means that the expandable area
    * is hidden.
    *
    * The default value of this property is @c false.
    *
    * @since BlackBerry 10.1.0
    */
    Q_PROPERTY(bool expanded READ isExpanded WRITE setExpanded RESET resetExpanded NOTIFY expandedChanged FINAL)

   /*!
    * @brief The visibility of the expandable indicator. The indicator hints that the @c TitleBar can be expanded. 
    *
    * The default value of this property is @c Default, which makes the indicator visible if content is set.
    *
    * @since BlackBerry 10.1.0
    */
    Q_PROPERTY(bb::cascades::TitleBarExpandableAreaIndicatorVisibility::Type indicatorVisibility READ indicatorVisibility 
        WRITE setIndicatorVisibility RESET resetIndicatorVisibility NOTIFY indicatorVisibilityChanged FINAL)

   /*!
    * @brief The toggle area for expanding and collapsing the expandable area.
    *
    * The toggle area is only active if the expandable indicator is visible.
    *
    * The default value of this property is @c Default, which uses the entire title bar for toggling the expandable area if content is set.
    *
    * @since BlackBerry 10.1.0
    */
    Q_PROPERTY(bb::cascades::TitleBarExpandableAreaToggleArea::Type toggleArea READ toggleArea 
        WRITE setToggleArea RESET resetToggleArea NOTIFY toggleAreaChanged FINAL)

public:
    virtual ~TitleBarExpandableArea();

    /*!
     * @brief Returns the expandable content of the @c TitleBar.
     *
     * @return The expandable content of the @c %TitleBar.
     *
     * @since BlackBerry 10.1.0
     */
     bb::cascades::Control* content() const;

    /*!
     * @brief Sets the expandable content of the @c TitleBar.
     *
     * @param content The expandable content of the @c %TitleBar.
     *
     * @since BlackBerry 10.1.0
     */
     Q_SLOT void setContent(bb::cascades::Control* content);

    /*!
     * @brief Resets the expandable content of the @c TitleBar to @c 0.
     *
     * @since BlackBerry 10.1.0
     */
     Q_SLOT void resetContent();

    /*!
     * @brief Returns the current expanded state.
     *
     *
     * @return @c true if expanded, and @c false if collapsed.
     *
     * @since BlackBerry 10.1.0
     */
     bool isExpanded() const;

    /*!
     * @brief Sets the expanded state.
     *
     * In the case of a successful expanded state change, the @c #expandedChanged(bool) signal is emitted.
     * It is possible to set the expanded state to @c true even if no content is set.
     * @param expanded The new state to set: @c true means expanded, @c false means collapsed.
     *
     * @since BlackBerry 10.1.0
     */
     Q_SLOT void setExpanded(bool expanded);

    /*!
     * @brief Resets the expanded state to @c false, which collapses the expandable area.
     * The @c expandedChanged signal is emitted when the expanded state is reset.
     *
     * @since BlackBerry 10.1.0
     */
     Q_SLOT void resetExpanded();

    /*!
     * @brief Returns the visibility of the expandable indicator.
     *
     * @return The visibility of the expandable indicator.
     *
     * @since BlackBerry 10.1.0
     */
     bb::cascades::TitleBarExpandableAreaIndicatorVisibility::Type indicatorVisibility() const;

    /*!
     * @brief Sets the visibility of the expandable indicator.
     *
     * @param visibility The visibility of the expandable indicator.
     *
     * @since BlackBerry 10.1.0
     */
     Q_SLOT void setIndicatorVisibility(bb::cascades::TitleBarExpandableAreaIndicatorVisibility::Type visibility);

    /*!
     * @brief Resets the visibility of the expandable indicator to @c Default.
     *
     * @since BlackBerry 10.1.0
     */
     Q_SLOT void resetIndicatorVisibility();

    /*!
     * @brief Returns the toggle area for expanding and collapsing the expandable area.
     *
     * @return The toggle area for expanding and collapsing the expandable area.
     *
     * @since BlackBerry 10.1.0
     */
     bb::cascades::TitleBarExpandableAreaToggleArea::Type toggleArea() const;

    /*!
     * @brief Sets the toggle area for expanding and collapsing the expandable area.
     *
     * @param toggleArea The toggle area for expanding and collapsing the expandable area.
     *
     * @since BlackBerry 10.1.0
     */
     Q_SLOT void setToggleArea(bb::cascades::TitleBarExpandableAreaToggleArea::Type toggleArea);

    /*!
     * @brief Resets the toggle area for expanding and collapsing the expandable area to @c Default.
     *
     * @since BlackBerry 10.1.0
     */
     Q_SLOT void resetToggleArea();

Q_SIGNALS:

    /*!
     * @brief Emitted when the expandable content of the @c TitleBar changes.
     *
     * @param newContent The new expandable content.
     *
     * @since BlackBerry 10.1.0
     */
     void contentChanged(bb::cascades::Control* newContent);

    /*!
     * Emitted when the expanded state has been changed.
     *
     * @param expanded The newly set expanded state
     *
     * @since BlackBerry 10.1.0
     */
     void expandedChanged(bool expanded);

    /*!
     * @brief Emitted when the visibility of the expandable indicator changes.
     *
     * @param visibility The new visibility.
     *
     * @since BlackBerry 10.1.0
     */
     void indicatorVisibilityChanged(bb::cascades::TitleBarExpandableAreaIndicatorVisibility::Type visibility);

    /*!
     * @brief Emitted when the area for toggling the expandable content.
     *
     * @param newToggleArea The new toggle area.
     *
     * @since BlackBerry 10.1.0
     */
     void toggleAreaChanged(bb::cascades::TitleBarExpandableAreaToggleArea::Type newToggleArea);

protected:
    /*! @cond PRIVATE */
    TitleBarExpandableArea();
    /*! @endcond */
  
private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(TitleBarExpandableArea)
    Q_DISABLE_COPY(TitleBarExpandableArea)
    /*! @endcond */
};

}
}

QML_DECLARE_TYPE(bb::cascades::TitleBarExpandableArea)

#endif // BB_CASCADES_TITLEBAREXPANDABLEAREA_H
