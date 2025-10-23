/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_PLACES_PLACEPICKER_HPP
#define BB_CASCADES_PLACES_PLACEPICKER_HPP

/*!
 * @file PlacePicker.hpp
 *
 * @since BlackBerry 10.0.0
 */

#include <bb/cascades/places/Global>
#include <bb/cascades/places/SelectedPlace>

#include <bb/cascades/CustomControl>
#include <QObject>

namespace bb
{
namespace cascades
{
namespace places
{

class PlacePickerPrivate;

/*!
 * @class PlacePicker
 *
 * @brief An interface that allows the user to browse and select a place from the
 * local Places database of contacts, favorites, and recent places as well as from remote search results.
 *
 * @c PlacePicker is one of the Places UI components that extends the Cascades @c CustomControl class.
 * The picker consists of a set of sheets. Each sheet takes up the whole screen and runs in modal mode. The
 * caller program is blocked until the user has selected a place or canceled the operation. The
 * returned @c SelectedPlace object pointer is the result of the selection. A non null pointer indicates
 * that a place has been successfully selected.
 *
 * The following example creates the @c PlacePicker and shows the UI for the user to browse and select a
 * place.
 *
 *  @code
 * #include <bb/cascades/places/PlacePicker>
 * #include <bb/cascades/places/SelectedPlace>
 *
 * QScopedPointer<PlacePicker> picker = new PlacePicker();
 * SelectedPlace *sp = picker->show();
 * if (sp != NULL) {
 *   // Extract details from SelectedPlace object.
 *   label.text(sp->name());
 *
 *   // Detach sp from parent picker so we still can use it
 *   // after the picker is destroyed.
 *   sp->setParent(NULL);
 * } else {
 *   // Either the user has canceled the operation
 *   // or the location capability is not enabled.
 * }
 * // Destruction of the picker pointer is handled by QScopedPointer
 *  @endcode
 *
 *  Or you can use the parent parameter in the constructor.
 *
 *  @code
 * #include <bb/cascades/places/PlacePicker>
 * #include <bb/cascades/places/SelectedPlace>
 *
 * PlacePicker *picker = new PlacePicker(pContainer);
 * SelectedPlace *sp = picker->show();
 * if (sp != NULL) {
 *   // Extract details from SelectedPlace object.
 *   label.text(sp->name());
 * } else {
 *   // Either the user has canceled the operation
 *   // or the location capability is not enabled.
 * }
 * // Picker pointer is managed by pContainer,
 * // and will be destroyed when pContainer is destroyed.
 * // In a similar manner, sp pointer is managed by picker,
 * // and will be destroyed when picker is destroyed.
 *  @endcode
 *
 * Or you can use QML to create a @c PlacePicker and show the UI for the user to browse and select a
 * place.
 *
 *  @code
 * import bb.cascades.places 1.0
 *
 * Page {
 *   content: Container {
 *     Label {
 *       id: title
 *       text: "place name selected"
 *     }
 *     Button {
 *       text: "click to open Place Picker"
 *       onClicked: {
 *          var place = picker.show ()
 *          if (place) {
 *            title.text = place.name
 *          } else {
 *            title.text = "no place selected"
 *          }
 *        }
 *     }
 *   }
 *   attachedObjects: [
 *     PlacePicker {
 *       id: picker
 *     }
 *   ]
 * }
 *
 *  @endcode
 *
 * @note If you are working with an API level of 10.0,
 * you must register the @c PlacePicker and @c SelectedPlace custom controls in
 * your C++ main program to use @c PlacePicker in QML.
 *
 * @pre Requires @c libbbplatformplaces.so at runtime.
 *
 * @permissions Some functionality requires permission to use the location service.
 *
 * @headerfile PlacePicker.hpp <bb/cascades/places/PlacePicker>
 *
 * @see @c SelectedPlace
 *
 * @xmlonly
 * <apigrouping group="Location/Places"/>
 * <library name="bbcascadesplaces"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_CASCADES_PLACES_EXPORT PlacePicker: public bb::cascades::CustomControl
{

    Q_OBJECT

public:
    /*!
     * @brief Constructor of PlacePicker class.
     *
     * @param[in] parent The parent container or 0. If not 0, the ownership of the constructed
     * @c PlacePicker will be transferred to the parent.
     *
     * @since BlackBerry 10.0.0
     */
    explicit PlacePicker(QObject* parent = 0);

    /*!
     *  @brief Destructor of PlacePicker class
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~PlacePicker();

    /*!
     * @brief Shows @c PlacePicker as a modal dialog, quits after user has selected a place or canceled.
     *
     * @return A pointer to the place selected or a null pointer, which means either the user canceled, there was
     * an error, or the user does not have location/data access privileges.
     *
     * @warning The @c PlacePicker object is the @c QObject parent of the returned @c SelectedPlace object. If you
     * want to access @c SelectedPlace out of @c PlacePicker object's life cycle, you need
     * to reset the parent of the @c SelectedPlace object, for example, @c setParent(NULL).
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bb::cascades::places::SelectedPlace* show();

private:
    Q_DECLARE_PRIVATE(PlacePicker)
    Q_DISABLE_COPY(PlacePicker)

    PlacePickerPrivate * const d_ptr;
};

}
}
}

QML_DECLARE_TYPE(bb::cascades::places::PlacePicker)
#endif
