/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */


#ifndef BB_CASCADES_PLACES_PLACEPICKERCONTROL_HPP
#define BB_CASCADES_PLACES_PLACEPICKERCONTROL_HPP

/*!
 * @file PlacePickerControl.hpp
 *
 * @since BlackBerry 10.0.0
 */

#include <bb/cascades/places/Global>
#include <bb/cascades/CustomControl>

namespace bb
{
namespace cascades
{
namespace places
{

class SelectedPlace;
class PlacePickerControlPrivate;

/*!
 * @class PlacePickerControl
 *
 * @brief A simple control for the @c PlacePicker API.
 *
 * @details This class represents a simple control that invokes the @c PlacePicker API and
 * emits a signal when the user has selected a place or canceled the operation.
 *
 * The following example creates the @c PlacePickerControl in C++ and shows the UI for the
 * user to browse and select a place.
 *
 *  @code
 *
 * #include <bb/cascades/places/PlacePickerControl>
 * #include <bb/cascades/places/SelectedPlace>
 *
 * PlacePickerControl* ppc = new PlacePickerControl(container);
 * ppc->setMaxWidth(105.0f);
 * ppc->setMinWidth(105.0f);
 * connect(ppc, SIGNAL(selected(bb::cascades::places::SelectedPlace*)),
 *         this, SLOT(placeSelected(bb::cascades::places::SelectedPlace*)));
 * container->add(ppc);
 *
 *  @endcode
 *
 * Or you can use QML to create the @c PlacePickerControl and show the UI for the
 * user to browse and select a place.
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
 *     PlacePickerControl {
 *       onSelected: {
 *         if (result) {
 *           title.text = result.name
 *         } else {
 *           title.text = "no place selected"
 *         }
 *       }
 *     }
 *   }
 * }
 *
 * @endcode
 *
 * @note If you are working with an API level of 10.0,
 * you must register the @c PlacePickerControl in
 * your C++ main program to use the @c PlacePickerControl in QML.
 *
 * @pre Requires @c libbbplatformplaces.so at runtime
 *
 * @permissions Some functionality requires permission to use the location service.
 *
 * @headerfile PlacePickerControl.hpp <bb/cascades/places/PlacePickerControl>
 *
 * @xmlonly
 * <apigrouping group="Location/Places"/>
 * <library name="bbcascadesplaces"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_CASCADES_PLACES_EXPORT PlacePickerControl: public bb::cascades::CustomControl
{
    Q_OBJECT

public:
    /*!
     * @brief Creates and initializes the @c PlacePicker button.
     *
     * @param[in] parentContainer The parent container or 0. This parameter is optional and will default
     * to 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    explicit PlacePickerControl(bb::cascades::Container* parentContainer = 0);

    /*!
     * @brief Destructor declared to support binary compatibility.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~PlacePickerControl();

Q_SIGNALS:

    /*!
     * @brief Emitted when the user has selected a place or canceled.
     *
     * @param[out] result Pointer to @c SelectedPlace object, which contains the place
     * details. Null, if nothing is selected or user canceled.
     *
     * @warning @c PlacePickerControl is the @c QObject parent of the returned @c SelectedPlace object. If you
     * want to access @c SelectedPlace out of @c PlacePickerControl object's life cycle, you need
     * to reset the parent of the @c SelectedPlace object, for example, @c setParent(NULL).
     *
     * @since BlackBerry 10.0.0
     */
    void selected(bb::cascades::places::SelectedPlace* result);

private:
    Q_DISABLE_COPY(PlacePickerControl)
    Q_DECLARE_PRIVATE(PlacePickerControl)

    PlacePickerControlPrivate* d_ptr;

};

}
}
}

QML_DECLARE_TYPE(bb::cascades::places::PlacePickerControl)
#endif
