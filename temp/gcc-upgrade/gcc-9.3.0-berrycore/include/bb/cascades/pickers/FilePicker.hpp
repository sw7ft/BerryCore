/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_PICKERS_FILEPICKER_HPP
#define BB_CASCADES_PICKERS_FILEPICKER_HPP

#include <bb/cascades/pickers/FileType>
#include <bb/cascades/pickers/FilePickerSortFlag>
#include <bb/cascades/pickers/FilePickerViewMode>
#include <bb/cascades/pickers/FilePickerSortOrder>
#include <bb/cascades/pickers/FilePickerMode>
#include <bb/cascades/pickers/Global>
#include <bb/cascades/pickers/FilePickerSourceRestriction>
#include <bb/cascades/pickers/FilePickerError>
#include <bb/system/SecurityPerimeter>
#include <QObject>
#include <QFlags>
#include <QtDeclarative>

namespace bb {
namespace cascades {
namespace pickers {

class FilePickerPrivate;

/*!
* @headerfile FilePicker.hpp bb/cascades/pickers/FilePicker
*
* @brief  Allows the user to select a file or select a name and location for saving a file.
*
* @details
*
* The FilePicker class in Picker mode allows the user to traverse the folder hierarchy to select a file.
* The application invoking the FilePicker can provide the types of the files that are allowed and in
* the case of multiple file types, the default file type.
*
* The application invoking the FilePicker can also provide a custom filter and/or the directory that FilePicker displays when it opens. This
* overrides the filter and folders associated with the file type. The filter is a list of string patterns that supports wildcards.
* For example, if the filter string is "*.jpg", FilePicker lists files where the file has an extension of ".jpg".
*
* The user can click a file to make a selection, or press the Cancel button. In the first case, FilePicker emits the fileSelected()
* signal and closes. If the user presses the Cancel button, FilePicker emits the canceled() signal before closing.  In addition FilePicker emits
* error () signal and closes if it encounters an error that forces it to close.
*
* FilePicker can be opened in Saver mode. In this mode, the application invoking the FilePicker can provide the file type of
* content and the default name and location to save the content to. FilePicker displays the content of the default folder associated with the file type.
* The user can change the location and/or default name.
*
* FilePicker supports two view modes - List view and Grid view. The view mode is chosen based on the selected file type
* to display the content in the best possible way. For example, pictures and videos are displayed as a grid and documents are displayed as a list.
* While viewing, the user can toggle between list and grid view modes. The application can specify the view mode that FilePicker uses for display.
* This overrides the default view mode.
*
* The default view in the FilePicker is the content on the local device. However, the user can access sources other than on the local device,
* for example, Cloud services, USB, and so on.
*
* In QML, you must prefix the absolute file path of an external resource with @c  file:// or your app won't be able to access the resource.
* File paths returned from @c FilePicker must be prefixed with @c  file:// to be used as an absolute path to @c ImageView or @c MediaPlayer.
*
* The following example creates a FilePicker in Picker mode with a file type of Picture:
*
* @code
*       FilePicker* filePicker = new FilePicker();
*       filePicker->setType(FileType::Picture);
*       filePicker->setTitle("Select Picture");
*       filePicker->setMode(FilePickerMode::Picker);
*       filePicker->open();
*
*       // Connect the fileSelected() signal with the slot.
*       QObject::connect(filePicker, 
*           SIGNAL(fileSelected(const QStringList&)), 
*           this, 
*           SLOT(onFileSelected(const QStringList&)));
* 
*       // Connect the canceled() signal with the slot.
*       QObject::connect(filePicker, 
*           SIGNAL(canceled()), 
*           this, 
*           SLOT(onCanceled()));
* @endcode
*
* The above example creates a FilePicker and sets the title as "Select Picture".
* FilePicker initially displays the contents of folders associated with the file type Picture,
* e.g. /accounts/1000/shared/photos, and displays only files that match the Picture file type.
*
* The following example creates a FilePicker in Saver mode with a file type of Document.
*
* @code
* FilePicker* filePicker = new FilePicker(FileType::Document, 0, 
*     QStringList(), QStringList(), QStringList("ImportantDoc.doc"));
* filePicker->setMode(FilePickerMode::Saver);
* filePicker->open();
* @endcode
*
* In the above example, FilePicker displays the contents of the folder associated with the file type Document and displays the
* default file name, "ImportantDoc.doc". The user can change the name or location and click the save button to return to the application.
*
* In Saver mode, the user can either click the Cancel Button or the Save Button. In the first case, FilePicker emits the fileSelected()
* signal and closes, returning control back to the calling application. If the user clicks the Cancel button, FilePicker
* emits the canceled() signal before closing.
*
* Here is example of using FilePicker in QML:
*
* @code
*   import bb.cascades.pickers 1.0
*
*       Page {
*           content: Container {
*               Button {
*                   text: "FilePicker from QML"
*                   onClicked: {
*                       filePicker.open()
*                   }
*               }
*           }
*           attachedObjects: [
*               FilePicker {
*                   id:filePicker
*                   type : FileType.Picture
*                   title : "Select Picture"
*                   directories : ["/accounts/1000/shared/misc"]
*                   onFileSelected : {
*                       console.log("FileSelected signal received : " + selectedFiles);
*
*                       //make sure to prepend "file://" when using as a source for an ImageView or MediaPlayer
*                       myImageView.imageSource = "file://" + selectedFiles[0];
*
*                   }
*               }
*           ]
*       }
* @endcode
*
* @xmlonly
* <qml>
*    <class register="yes"/>
* </qml>
* <apigrouping group="Data management/File picker"/>
* <library name="bbcascadespickers"/>
* @endxmlonly
 *
 * @since BlackBerry 10.0.0
*/
class BB_CASCADES_PICKERS_EXPORT FilePicker : public QObject
{
        Q_OBJECT

        /*!
         * @brief Determines the mode of the FilePicker. FilePicker can be opened in Picker or Saver mode. By default,
         * FilePicker opens in Picker mode.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::pickers::FilePickerMode::Type mode READ mode WRITE setMode NOTIFY modeChanged FINAL)

        /*!
         * @brief Represents the type of file that can be viewed in the FilePicker. FileType determines the filter, sort order, and view mode
         * in the FilePicker.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::pickers::FileType::Types type READ type WRITE setType NOTIFY typeChanged FINAL)

        /*!
         * @brief Represents the default file type if multiple file types are specified in FilePicker.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::pickers::FileType::Types defaultType READ defaultType WRITE setDefaultType NOTIFY defaultTypeChanged FINAL)

        /*!
         * @brief The title for the FilePicker. This is displayed on the title bar of the FilePicker
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)

        /*!
         * @brief The name of one or more files in Saver or SaverMultiple mode.
         * In Saver mode, FilePicker takes the first one from this list as the default file name.  This default file name can be changed in
         * FilePicker.
         *
         * In SaverMultiple mode, the application can provide a list of file names.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QStringList defaultSaveFileNames READ defaultSaveFileNames WRITE setDefaultSaveFileNames NOTIFY defaultSaveFileNamesChanged FINAL)

        /*!
         * @brief Indicates whether FilePicker will append a number to the file name to make it unique in Saver mode. If set to true, FilePicker
         * will not check for uniqueness of the selected file name.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool allowOverwrite READ allowOverwrite WRITE setAllowOverwrite NOTIFY allowOverwriteChanged FINAL)

        /*!
         * @brief The application invoking FilePicker can provide the list of directories where the files are most likely to be found. In Picker mode,
         * these directories are added to list of associated folders. In Saver mode, the FilePicker will navigate to the first directory
         * in the list.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QStringList directories READ directories WRITE setDirectories NOTIFY directoriesChanged FINAL)

        /*!
         * @brief The files in the FilePicker will be filtered based on this filter.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QStringList filter READ filter WRITE setFilter NOTIFY filterChanged FINAL)

        /*!
         * @brief Determines whether FilePicker displays the content in a list view or a grid view. By default, FilePicker chooses the ViewMode
         * based on the file type. For example, pictures are displayed in grid view.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::pickers::FilePickerViewMode::Type viewMode READ viewMode WRITE setViewMode NOTIFY viewModeChanged FINAL)

        /*!
         * @brief Determines the attribute to sort the content in the FilePicker. By default, FilePicker choose the sort flag
         * based on the file type.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::pickers::FilePickerSortFlag::Type sortBy READ sortBy WRITE setSortBy NOTIFY sortByChanged FINAL)

        /*!
         * @brief Determines the sort order for the content in the FilePicker. By default, FilePicker choose the sort order
         * based on the file type.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::pickers::FilePickerSortOrder::Type sortOrder READ sortOrder WRITE setSortOrder NOTIFY sortOrderChanged FINAL)

        /*!
         * @brief Indicates whether to enable image cropping in the FilePicker.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool imageCropEnabled READ isImageCropEnabled WRITE setImageCropEnabled NOTIFY imageCropEnabledChanged FINAL)

        /*!
         * @brief Indicates the security perimeter for the FilePicker.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::system::SecurityPerimeter::Type perimeter READ perimeter WRITE setPerimeter NOTIFY perimeterChanged FINAL)

        /*!
		 * @brief Determines which sources FilePicker displays. By default, FilePicker displays all sources.
		 *
		 *
		 * @since BlackBerry 10.2.0
		 */
		Q_PROPERTY(bb::cascades::pickers::FilePickerSourceRestriction::Type sourceRestriction READ sourceRestriction WRITE setSourceRestriction NOTIFY sourceRestrictionChanged FINAL)

public:

    /*!
     *  @brief Constructs a %FilePicker in Picker mode.
     *  By default, the contents of the root folder based on application perimeter will be displayed, e.g. /accounts/1000/shared
     *
     *  @code
     *      FilePicker* FilePicker = new FilePicker();
     *  @endcode
     *  @param parent The parent or 0. If not 0, the ownership of constructed FilePicker will be transferred to parent.
     *
     * @since BlackBerry 10.0.0
    */
    explicit FilePicker(QObject* parent = 0);

    /*!
     * @brief Constructs a %FilePicker with the file type of the file to select. In Picker mode, the application can provide multiple file types.
     * For a single file type, FilePicker displays the aggregated view of folders associated with file type. The contents of the
     * directory are filtered based on the type provided. If multiple file types are provided, FilePicker opens up by default,
     * to the aggregated view of folders associated with the default file type
     *
     * @code
     * // For a single type
     *      FilePicker* FilePicker = new FilePicker(FileType::Picture, 0, QStringList(), QStringList(), QStringList());
     *
     * // For multiple types
     *      FilePicker* FilePicker = new FilePicker(FileType::Picture | FileType::Video, FileType::Picture, QStringList(), QStringList(), QStringList() );
     *
     * @endcode
     *
     *  In the above example, the application provided two file types,Picture and Video, with Picture as the default type.
     *  FilePicker will show a drop down with two entries, Picture and Video, and Picture will be selected by default. If the user chooses any of the
     *  other file types, the view will be updated to display the folders associated with the selected file type.
     *
     * The application can provide a list of directories that FilePicker can use for picking or saving files. In this case, the FilePicker
     * will add these directories to the list of folders associated with the file type and display them on open.
     *
     * In Saver mode, the application will provide a single file type and FilePicker will open the default folder associated with the file type.
     * The application can optionally provide the default file name and location of the file to save. In this case, FilePicker will open the default
     * location and display the provided file name. If the application provides multiple locations, the FilePicker will navigate to the first one.
     *
     * @param fileType         The type of files to display in FilePicker
     * @param defaultFileType  defaultfileType or 0. If more than one Type is specified in the first parameter, FilePicker will display the
     *                         content of defaultFileType
     * @param filterList       The filter used to filter the content in FilePicker. This filter will override the default filter associated with the
     *                         file Type. Each filter in the list is a string pattern that supports wildcards ("*"). The files with extensions that match
     *                         this filter will be displayed.
     * @param directories      The list containing the complete path to folders. These folders will be added to the list of folders associated with the file type.
     *                         In Saver mode, only the first folder in the list will be used.
     * @param defaultSaveFileNames The list of one or more default file names in Saver Mode.
     * @param parent           The parent or 0. If not 0, the ownership of the constructed FilePicker will be transferred to parent.
     *
     * @since BlackBerry 10.0.0
     */
     explicit FilePicker(FileType::Types fileType, FileType::Types defaultFileType, const QStringList& filterList, const QStringList& directories, const QStringList& defaultSaveFileNames, QObject* parent = 0);

    //!@cond  PRIVATE
    /*!
     * Constructs a %FilePicker with the file type of the file to select. In Picker mode, the application can provide multiple file types.
     * For a single file type, FilePicker will display the aggregated view of folders associated with the file type. The contents of the
     * directory are filtered based on the type provided. If multiple file types are provided, FilePicker will open up by default,
     * to the aggregated view of folders associated with the default file type.
     *
     * This constructor is here to maintain backward compatibility.
     *
     * @code
     * For a single type:
     *      FilePicker* FilePicker = new FilePicker(FileType::Picture);
     *
     * For multiple types:
     *      FilePicker* FilePicker = new FilePicker(FileType::Picture | FileType::Video, FileType::Picture);
     *
     *  In the above example, the application provided two file types, Picture and Video, with Picture as the default type.
     *  FilePicker will show a drop down with two entries, Picture and Video, and Picture will be selected by default. If the user chooses any of the
     *  other file types, the view will be updated to display the folders associated with the selected file type.
     *
     * @endcode
     *
     * The application can provide a list of directories that FilePicker can use for picking or saving the file. In this case, the FilePicker
     * will add these directories to the list of folders associated with the file type and display them on open.
     *
     * In Saver mode, the application will provide a single file type and FilePicker will open the default folder associated with the file type.
     * The application can optionally provide the default file name and location of the file to save. In this case, FilePicker will open the default
     * location and display the provided file name. If the application provides multiple locations, the FilePicker will navigate to the first one.
     *
     * @param fileType         The type of files to display in FilePicker
     * @param defaultFileType  defaultfileType or 0. If more than one Type is specified in the first parameter, FilePicker will display the
     *                         content of defaultFileType.
     * @param filterList       The filter used to filter the content in FilePicker. This filter will override the default filter associated with the
     *                         file Type. Each filter in the list is a string pattern that supports wildcards ("*"). The files with extensions that match
     *                         this filter will be displayed.
     * @param directories      The list containing the complete path to folders. These folders will be added to the list of folders associated with the file type.
     *                         In Saver mode, only the first folder in the list will be used.
     * @param defaultSaveFileName default file names in Saver Mode.
     * @param parent           The parent or 0. If not 0, the ownership of constructed FilePicker will be transferred to parent.
     */
    explicit FilePicker(FileType::Types fileType, FileType::Types defaultFileType = 0, const QStringList& filterList = QStringList(), const QStringList& directories = QStringList(), const QString& defaultSaveFileName = QString(), QObject* parent = 0) BB_DEPRECATED;
  //!@endcond  PRIVATE

    /*!
     * @brief Destructor for FilePicker
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~FilePicker();

    /*!
     * @brief Opens up the FilePicker. This will display the FilePicker, allowing the user to navigate the folders and select the file.
     * When the selection is made, the fileSelected() signal is emitted with the absolute path of the selected files.
     * If the selection is canceled, the canceled() signal is emitted.
     *
     * Attribute of FilePicker must be set before calling the open() method. Any call to setters after open() is called will be ignored
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void open();

    /*!
     * @brief Indicates whether the FilePicker will open in Picker or Saver mode.
     * By default, the FilePicker will open in Picker mode.
     *
     * @param mode FilePicker will open in this mode
     *
     * @since BlackBerry 10.0.0
     */
    void setMode(bb::cascades::pickers::FilePickerMode::Type mode);

    /*!
     * @brief Returns whether the FilePicker is in Picker Mode or Saver Mode
     * @return FilePickerMode::Mode
     * @see setMode(), Mode
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::pickers::FilePickerMode::Type mode() const;

    /*!
     * @brief Sets the title of the FilePicker. This title is displayed at the top.
     *
     * @param title
     *
     * @since BlackBerry 10.0.0
     */
    void setTitle(const QString& title);

    /*!
     * @brief Returns the FilePicker title if it is available.
     *
     * @return QString
     * @see setTitle()
     *
     * @since BlackBerry 10.0.0
     */
    QString title() const;

    /*!
     * @brief Sets the list of one or more default or suggested file name(s) in FilePicker in Saver mode. For a single file name, the name will be displayed in FilePicker
     * and can be changed.
     * In Picker mode, FilePicker will ignore the value of defaultSaveName.
     *
     * @param defaultSaveName A list of one of more default file names
     *
     * @since BlackBerry 10.0.0
     */
    void setDefaultSaveFileNames(const QStringList& defaultSaveName);

    /*!
     * @brief Returns the default file names set earlier using the setDefaultSaveFileNames in FilePicker in Saver mode. This method will return an empty list
     * in Picker mode.
     *
     * @return the list of default save file names
     * @see setDefaultSaveFileNames()
     *
     * @since BlackBerry 10.0.0
     */
    QStringList defaultSaveFileNames() const;

    //!@cond  PRIVATE
    /*!
     * @brief Sets the file name in FilePicker in Saver mode. This name is displayed in FilePicker
     * and can be changed.
     *
     * In Picker mode, FilePicker will ignore the value of defaultSaveName.
     *
     * This method is deprecated. Use setDefaultSaveFileNames instead
     *
     * @param defaultSaveName default file name
     */
    void setDefaultSaveFileName(const QString& defaultSaveName) BB_DEPRECATED;
   //!@endcond  PRIVATE

     //!@cond  PRIVATE*/
    /*!
     * @brief Returns the default file names set earlier using the setDefaultSaveFileName in FilePicker in Saver mode. This method will return an empty string
     * in Picker mode.
     *
     * This method is deprecated. Use defaultSaveFileNames instead
     *
     * @return the list of default save file name
     * @see setDefaultSaveFileNames()
     */
    QString defaultSaveFileName() const BB_DEPRECATED;
   //!@endcond  PRIVATE*/

    /*!
     * @brief Indicates whether the FilePicker should allow the user to specify a file name that already exists.
     * If allowOverwrite is set to true, FilePicker will not check for uniqueness of a file name.
     *
     * If allowOverwrite is set to false, the FilePicker will ensure that the file name is unique by adding
     * a suffix to the name.
     *
     * @return Returns True if the name can be overwritten, false otherwise
     * @see setAllowOverwrite()
     *
     * @since BlackBerry 10.0.0
     */
    bool allowOverwrite() const;

    /*!
     * @brief Indicates whether or not the FilePicker should generate a unique file name if the file name already exists. If it is set to false,
     * FilePicker will ensure that the file name is unique by adding a suffix to the name. If it is set to true, the FilePicker will
     * not check for the uniqueness of the file name.
     *
     * By default, the allowOverwrite will be set to false. This flag will be used only when the FilePicker is in Saver or SaverMultiple mode
     *
     * @param overwrite
     *
     * @see allowOverwrite()
     *
     * @since BlackBerry 10.0.0
     */
    void setAllowOverwrite(bool overwrite);

    /*!
     * @brief Sets a list of one or more directories to pick or save the file. The FilePicker, in Picker Mode, will add these directories to
     * the list of associated folders. In Saver Mode, FilePicker will navigate to the first directory in the list. If the directories are not
     * specified, FilePicker, in Picker Mode, will display the folders associated with the specified file type or navigate to the default
     * folder in Saver Mode
     *
     *
     * Warning: This behavior will be deprecated. In the future when specifying 
     *          multiple directories, the first directory in the list will be used, 
     *          but the rest of the directories in the list will be ignored.
     * 
     * @code
     *      FilePicker *picker = new FilePicker();
     *      picker->setType(FileType::Document);
     *      picker->setDirectories("/accounts/1000/shared/temp");
     * @endcode
     * In the above example, FilePicker will add "/accounts/1000/shared/temp" to its list of associated folders for FileType Document.
     *
     * @param directories The list containing the complete path to the folders for where to pick or save the file
     *
     * @since BlackBerry 10.0.0
     */
    void setDirectories(const QStringList& directories);

    /*!
     * @brief Returns the folder(s) for where to pick or save the file.
     *
     * @return directories  The list of folders from where to pick or save the file
     * @see setDirectories()
     *
     *
     * @since BlackBerry 10.0.0
     */
    QStringList directories() const;

    /*!
     *  @brief Sets the file type(s) of the files that can be selected in the FilePicker. One or more file types can be combined by using an OR operator.
     *  The FilePicker will filter the content based on the type(s) provided.
     *
     *  @param fileType The file type(s) of the files that will be displayed
     *
     * @since BlackBerry 10.0.0
     */
    void setType(bb::cascades::pickers::FileType::Types fileType);

    /*!
     *  @brief Gets the file type(s) from the FilePicker.
     *  Types is typedef for QFlags<Type>. It stores an OR combination of Type values.
     *
     *  @return Types
     *  @see setType()
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::pickers::FileType::Types type() const;

    /*!
     * @brief Sets the default file type. The default file type is used if an application provides multiple file types.
     * @param fileType FilePicker will display this fileType if the application provide multiple
     * file types
     *
     * @since BlackBerry 10.0.0
     */
    void setDefaultType(bb::cascades::pickers::FileType::Types fileType);

    /*!
     * @brief Returns the default file type. The default file type is used if an application provides multiple file types.
     *
     * @return Default type
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::pickers::FileType::Types defaultType() const;

    /*!
     * @brief Sets the filter. FilePicker will use this filter to filter the content of the folders associated with a file type.
     * If the filter is not specified, the content will be filtered based on file type.
     *
     * @code
     *      FilePicker *picker = new FilePicker();
     *      picker->setType(FileType::Picture);
     *      QStringList filters;
     *      filters << "*.jpg" << "*.bmp";
     *      picker->setFilter(filters);
     * @endcode
     *
     * @param filter Filter list
     *
     * @since BlackBerry 10.0.0
     */
    void setFilter(const QStringList& filter);

    /*!
     * @brief Returns the filter set using the setFilter().
     * @return The list of filters
     *
     * @since BlackBerry 10.0.0
     */
    QStringList filter() const;

    /*!
     * @brief Sets whether the FilePicker displays the content in List View or Grid View. If the ViewMode is not specified, FilePicker
     * will choose to display the files based on the FileType.
     *
     * @param mode
     *
     * @since BlackBerry 10.0.0
     */
    void setViewMode(bb::cascades::pickers::FilePickerViewMode::Type mode);

    /*!
     * @brief Returns the viewMode set using setViewMode.
     *
     * @return ViewMode::Mode
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::pickers::FilePickerViewMode::Type viewMode() const;

    /*!
     * @brief Sets the attribute that FilePicker will use to sort the content. If the FilePickerSortFlag is not specified, FilePicker will
     * choose the sort flag based on the file type specified.
     *
     * @param sortBy The attribute to sort on.
     *
     * @since BlackBerry 10.0.0
     */
    void setSortBy(bb::cascades::pickers::FilePickerSortFlag::Type sortBy);

    /*!
     * @brief Returns the sort attribute set using setSortBy.
     *
     * @return FilePickerSortFlag
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::pickers::FilePickerSortFlag::Type sortBy() const;

    /*!
      * @brief Sets the sort order. If the sort order is not specified, FilePicker will choose the sort order based on the file type
      * @param order Sort Order
     *
     * @since BlackBerry 10.0.0
     */
    void setSortOrder(bb::cascades::pickers::FilePickerSortOrder::Type order);

    /*!
     * @brief Returns the sortOrder set using setSortOrder.
     * @return FilePickerSortOrder
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::pickers::FilePickerSortOrder::Type sortOrder() const;

    /*!
     * @brief Indicates whether to allow cropping of image in FilePicker in Picker mode. This is only applicable for a file type of Picture.
     * By default, image cropping is disabled.
     * @param imageCrop Enable or disable cropping of images.
     *
     * @since BlackBerry 10.0.0
     */
    void setImageCropEnabled(bool imageCrop);

    /*!
     * @brief Returns whether image cropping is enabled.
     * @return bool Returns true if the image cropping is enabled in FilePicker, otherwise returns false
     *
     * @since BlackBerry 10.0.0
     */
    bool isImageCropEnabled() const;

    /*!
     * @brief Sets the security perimeter in which FilePicker should be invoked. If the security perimeter is not specified
     * FilePicker uses the environment variable 'PERIMETER' to determine the perimeter.
     *
     * @param perimeter Security perimeter in which FilePicker will be invoked
     *
     * @since BlackBerry 10.0.0
     */
    void setPerimeter(bb::system::SecurityPerimeter::Type perimeter);

    /*!
     * @brief Returns the security perimeter in which FilePicker should be invoked.
     *
     * @return Security perimeter in which FilePicker will be invoked
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SecurityPerimeter::Type perimeter() const;

    /*!
     * @brief Returns the absolute paths of the files that were selected in the FilePicker, in Picker or Saver mode.
     * If no files were selected, an empty list is returned. Calling this method before the selection is made will return an
     * empty list.
     *
     * @return QStringList Returns a list of the absolute paths of the selected files, or an empty list if no files were selected.
     *
     * @since BlackBerry 10.0.0
     */
    QStringList selectedFiles();

    /*!
     * @brief Closes the FilePicker.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void close();

    /*!
	 * @brief Sets which sources FilePicker displays. By default, FilePicker displays all sources.
	 *
	 * @param mode
	 *
	 * @since BlackBerry 10.2.0
	 */
	void setSourceRestriction(bb::cascades::pickers::FilePickerSourceRestriction::Type mode);

	/*!
	 * @brief Returns the sourceRestriction set using setSourceRestriction.
	 *
	 * @return FilePickerSourceRestriction
	 *
	 * @since BlackBerry 10.2.0
	 */
	bb::cascades::pickers::FilePickerSourceRestriction::Type sourceRestriction() const;


Q_SIGNALS:
    /*!
     * @brief Emitted when a selection has been made in the FilePicker in Picker or Saver mode.
     *
     * @param selectedFiles A list containing the absolute path of the selected files
     *
     * @since BlackBerry 10.0.0
     */
    void fileSelected(const QStringList& selectedFiles);

    /*!
     * @brief Emitted when the cancel button is clicked in the FilePicker.
     *
     * @since BlackBerry 10.0.0
     */
    void canceled();

    /*!
     * @brief Emitted when the FilePicker is opened.
     *
     * @since BlackBerry 10.0.0
     */
    void pickerOpened();

    /*!
     * @brief Emitted when the FilePicker is closed.
     *
     * @since BlackBerry 10.0.0
     */
    void pickerClosed();

    /*!
     * @brief Emitted when the Mode property changes.
     * @param newMode The new Mode of the FilePicker
     *
     * @since BlackBerry 10.0.0
     */
    void modeChanged(bb::cascades::pickers::FilePickerMode::Type newMode);

    /*!
     * @brief Emitted when the File type property changes.
     * @param newType The new FileType of the file to display in FilePicker
     *
     * @since BlackBerry 10.0.0
     */
    void typeChanged(bb::cascades::pickers::FileType::Types newType);

    /*!
     * @brief Emitted when the default File type property changes.
     * @param newDefaultType The new default FileType to display in FilePicker
     *
     * @since BlackBerry 10.0.0
     */
    void defaultTypeChanged(bb::cascades::pickers::FileType::Types newDefaultType);

    /*!
     * @brief Emitted when the title property changes.
     * @param newTitle The new title for the FilePicker
     *
     * @since BlackBerry 10.0.0
     */
    void titleChanged(const QString& newTitle);

    /*!
     * @brief Emitted when the defaultSaveFileNames property changes.
     * @param newSaveFileNames The new list of save File Names
     *
     * @since BlackBerry 10.0.0
     */
    void defaultSaveFileNamesChanged(const QStringList& newSaveFileNames);

    /*!
     * @brief Emitted when the allowOverwrite property changes.
     * @param allowOverwrite True if the FilePicker can return a file name that already exist, false otherwise
     *
     * @since BlackBerry 10.0.0
     */
    void allowOverwriteChanged(bool allowOverwrite);

    /*!
     * @brief Emitted when the directories property changes.
     * @param newDirectories The new list of folders
     *
     * @since BlackBerry 10.0.0
     */
    void directoriesChanged(const QStringList& newDirectories);

    /*!
     * @brief Emitted when the filter property changes.
     * @param newFilter The new filter for the FilePicker
     *
     * @since BlackBerry 10.0.0
     */
    void filterChanged(const QStringList& newFilter);

    /*!
     * @brief Emitted when the viewMode property changes.
     * @param newViewMode The new viewMode for the FilePicker
     *
     * @since BlackBerry 10.0.0
     */
    void viewModeChanged(bb::cascades::pickers::FilePickerViewMode::Type newViewMode);

    /*!
     * @brief Emitted when the sortBy property changes.
     * @param newSortBy The new sort attribute to sort the FilePicker content
     *
     * @since BlackBerry 10.0.0
     */
    void sortByChanged(bb::cascades::pickers::FilePickerSortFlag::Type newSortBy);

    /*!
     * @brief Emitted when the sortOrder property changes.
     * @param newSortOrder The new sort order for the FilePicker content
     *
     * @since BlackBerry 10.0.0
     */
    void sortOrderChanged(bb::cascades::pickers::FilePickerSortOrder::Type newSortOrder);

    /*!
     * @brief Emitted when the imageCropEnabled property changes in Picker mode.
     * @param enable If this value is true, imageCropping is enabled in FilePicker.
     * If this value is false, imageCropping is disabled.
     *
     * @since BlackBerry 10.0.0
     */
    void imageCropEnabledChanged(bool enable);

    /*!
     * @brief Emitted when the perimeter property changes.
     *
     * @param perimeter Security perimeter for FilePicker
     *
     * @since BlackBerry 10.0.0
     */
    void perimeterChanged(bb::system::SecurityPerimeter::Type perimeter);

    /*!
     * @brief Emitted when the sourceRestriction property changes.
     * @param newSourceRestriction The new sourceRestriction for the FilePicker
     *
     * @since BlackBerry 10.2.0
     */
    void sourceRestrictionChanged(bb::cascades::pickers::FilePickerSourceRestriction::Type newSourceRestriction);

    /*!
     * @brief Emitted when the picker is forced to close due to an error.
     *
     * @param error The encountered error
     *
     * @since BlackBerry 10.2.0
     */
    void error(bb::cascades::pickers::FilePickerError::Type error);

	
	/*!
	* @xmlonly
	* <qml>
	* <param name="perimeter" type="bb::system::SecurityPerimeter::Type"/>
	* </qml>
	* @endxmlonly
	*/
	void perimeterChanged(int perimeter);

private:
   //!@cond  PRIVATE
    Q_DECLARE_PRIVATE(FilePicker)
    Q_DISABLE_COPY(FilePicker)
    FilePickerPrivate* d_ptr;
   //!@endcond  PRIVATE
};


}  /* namespace pickers */
} /* namespace cascades*/
} /* namespace bb */


#endif /* BB_CASCADES_PICKERS_FILEPICKER_HPP */
