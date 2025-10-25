/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef CASCADES_PICKERITEMPROVIDER_H
#define CASCADES_PICKERITEMPROVIDER_H

#include <QVariantList>
#include <bb/cascades/BaseObject>
#include <bb/cascades/bbcascades_global.h>

namespace bb {
    namespace cascades {

    class Picker;
    class PickerProviderPrivate;
    class VisualNode;

    /*!
    *
    * @brief An interface for providing @c VisualNode objects as items in a @c Picker.
    *
    * When you implement a @c %PickerProvider, the following functions are required:
    * - @c createItem(): creates an empty @c VisualNode object for the @c Picker,
    *    to be used as a picker item
    * - @c updateItem(): updates an existing picker item for a particular cell in the @c %Picker
    * - @c columnCount(): gets the number of columns in the @c %Picker
    *
    * Here is how the @c %PickerProvider can be attached to the @c %Picker.
    *
    * QML:
    *
    * @code
    * Picker {
    *     id: picker
    *     title: "Select items";
    *     onCreationCompleted: {
    *         picker.setPickerItemProvider(provider)
    *     }
    *     attachedObjects: [
    *         CustomPickerItemsProvider {
    *             id: provider
    *             columnWidthRatio: [ 2, 1 ]
    *         }
    *     ]
    * }
    * @endcode
    *
    * C++:
    *
    * @code
    * Picker *picker = Picker::create().title("Title");
    * PickerProvider *itemProvider = new MyPickerProvider();
    * picker->setPickerItemProvider(itemProvider);
    * @endcode
    *
    * @xmlonly
    * <apigrouping group="User interface/Core controls"/>
    * @endxmlonly
     *
     * @since BlackBerry 10.1.0
    */

    class BBCASCADES_EXPORT PickerProvider : public BaseObject {
        Q_OBJECT
        /*!
         * @brief Column width ratio defining widths of the @c Picker columns.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(QVariantList columnWidthRatio
                   READ columnWidthRatio
                   WRITE setColumnWidthRatio
                   RESET resetColumnWidthRatio
                   NOTIFY columnWidthRatioChanged FINAL)

    public:
        explicit PickerProvider(QObject *parent = 0);
        virtual ~PickerProvider();

        static const int NoBoundary;

        /*!
        * @brief Called to create a new item for the @c Picker.
        *
        * @param pickerList The generic picker control sending the request.
        * @param columnIndex The column which the item will be added to.
        *
        * @return The @c VisualNode pointer.
         *
         * @since BlackBerry 10.1.0
        */
        virtual VisualNode* createItem(Picker* pickerList, int columnIndex) = 0;

        /*!
        * @brief Called to update the content for a picker item.
        *
        * @param pickerList  The generic picker control sending the request.
        * @param columnIndex The column which the item is shown in.
        * @param rowIndex    The item index this node is mapped to on the server.
        * @param pickerItem  Pointer to the picker item to update.
        *
         *
         * @since BlackBerry 10.1.0
        */
        virtual void updateItem(Picker* pickerList, int columnIndex, int rowIndex, VisualNode* pickerItem) = 0;

        /*!
        * @brief Gets the number of columns for this provider.
        * @return The number of columns for this provider.
         *
         * @since BlackBerry 10.1.0
        */
        virtual int columnCount() const = 0;

        /*!
         * @brief Gets the lower and upper boundaries for the column.
         *
         * @param[in] column The column index.
         * @param[out] lowerBoundary The lower boundary for the column.
         * @param[out] upperBoundary The upper boundary for the column.
         *
         * @since BlackBerry 10.1.0
         */
        virtual void range(int column, int* lowerBoundary, int* upperBoundary);

        /*!
         * @brief This method maps a list of indices to the corresponding value.
         *
         * @param picker The pointer to the picker control.
         * @param indices A list of indices to get the value for.
         * @return QVariant holding values representing the list of indices.
         *
         * @since BlackBerry 10.1.0
         */
        virtual QVariant value(Picker *picker, const QList<int> &indices) const;

        /*!
         * @brief Finds the picker item corresponding to the specified value.
         *
         * @param picker The pointer to the picker control.
         * @param value The value.
         * @return The list of indices corresponding to the value, or empty list if the value cannot be located
         *
         * @since BlackBerry 10.1.0
         */
        virtual QList<int> indicesOf(Picker *picker, const QVariant &value) const;

        /*!
         * @brief Gets the width ratio for columns in the picker control.
         *
         * @return The list of width ratio for columns
         *
         * @since BlackBerry 10.1.0
         */
        QVariantList columnWidthRatio();

        /*!
         * @brief Sets width ratio for columns of picker control.
         *
         * @param ratio List of int-values specifying the relative width factor.
         *
         * @since BlackBerry 10.1.0
         */
        void setColumnWidthRatio(const QVariantList &ratio);

        /*!
         * @brief Resets the width ratio for columns in the picker control.
         *
         * @since BlackBerry 10.1.0
         */
        void resetColumnWidthRatio();

    Q_SIGNALS:
        /*!
         * @brief Emitted when the @c Picker that uses this @c PickerProvider
         * should call @c updateItem() for all of its cached items.
         *
         * The @c %PickerProvider implementation should typically emit this signal
         * when an application wants to change the visual appearance of all
         * items in a @c %Picker.
         *
         * @param column Number of column to update.
         *
         * @since BlackBerry 10.1.0
         */
        void itemUpdatesNeeded(int column);
        /*!
         * @brief Emitted when the column width ratio changes
         *
         * @param ratio The new column width ratio
         *
         * @since BlackBerry 10.1.0
         */
        void columnWidthRatioChanged(const QVariantList &ratio);

        /*!
         * @brief Emitted when the column range is changed and should be updated
         *
         * @param column The column index for which the boundaries should be updated
         *
         * @since BlackBerry 10.1.0
         */
        void updateRange(int column);

    private:
        Q_DECLARE_PRIVATE(PickerProvider)
        Q_DISABLE_COPY(PickerProvider)
    };

    } // cascades
} // bb

#endif /* CASCADES_PICKERITEMPROVIDER_H */
