/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef bb_cascades_fontsize_h
#define bb_cascades_fontsize_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 * @brief Represents the types of font sizes for a @c TextStyle.
 *
 * This enumeration represents logical font sizes that will be translated
 * to actual sizes according to the font size set in the device's accessibility settings.
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT FontSize {
private:
  Q_GADGET
  Q_ENUMS (Type)
public:
  /*!
   * @brief Types of font sizes
   *
   * @since BlackBerry 10.0.0
   */
  enum Type {
    /*! 
     * @brief The default font size.
     *
     * @since BlackBerry 10.0.0
     */
    Default = 0,
    /*! 
     * @brief Indicates that an exact font size defined in post script points (which is 
     * independent of global font settings) should be used instead of a logical size.
     *     
     * This setting must be used in combination with the @c fontSizeValue property on
     * the @c TextStyle.
     *
     * @since BlackBerry 10.0.0
     */
    PointValue = 1,
    /*! 
     * @brief Indicates that a percentage of the parent style element's size should be used.
     *     
     * This setting must be used in combination with the @c fontSizeValue property on the 
     * @c TextStyle. If there is no parent element, the size will be in relation to the 
     * system default size, which typically matches the logical size of @c Medium.
     *
     * @since BlackBerry 10.0.0
     */
    PercentageValue = 2,
    /*! 
     * @brief An extra, extra small font size.
     *
     * This size is often used for large blocks of text and is roughly equivalent to an actual size of 5pt.
     *
     * @since BlackBerry 10.0.0
     */
    XXSmall = 70,
    /*! 
     * @brief An extra small font size.
     *
     * This size is often used for subtitles and is roughly equivalent to an actual size of 6pt.
     *
     * @since BlackBerry 10.0.0
     */
    XSmall = 80,
    /*! 
     * @brief A small font size.
     *
     * This size is often used for small blocks of text and is roughly equivalent to an actual size of 7pt.
     *
     * @since BlackBerry 10.0.0
     */
    Small =  90,
    /*! 
     * @brief A medium font size.
     *
     * This size is often used for body text and is roughly equivalent to an actual size of 8pt.
     *
     * @since BlackBerry 10.0.0
     */
    Medium = 100,
    /*! 
     * @brief A large font size.
     *
     * This size is often used for small headings and titles, and is roughly equivalent to an actual size of 9pt.
     *
     * @since BlackBerry 10.0.0
     */
    Large =  110,
    /*! 
     * @brief An extra large font size.
     *
     * This size is often used for headings and is roughly equivalent to an actual size of 11pt.
     *
     * @since BlackBerry 10.0.0
     */
    XLarge = 120,
    /*! 
     * @brief An extra, extra large font size.
     *
     * This size is often used for large headings and is roughly equivalent to an actual size of 13pt.
     *
     * @since BlackBerry 10.0.0
     */
    XXLarge = 130
  };

private:
  /*! @cond PRIVATE */
  FontSize();
  ~FontSize();
  /*! @endcond */
};

}
}

#endif // bb_cascades_fontsize_h
