/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef cascades_a11yrole_h
#define cascades_a11yrole_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
  namespace cascades {

    /*!
     * @brief A set of roles that can be used on accessibility objects
     * for use with assistive technologies.
     *
     * @xmlonly
     *     <apigrouping group="User interface/Accessibility"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.2.0
     */
    class BBCASCADES_EXPORT A11yRole
    {
        Q_GADGET
        Q_ENUMS(Type)

    public:
        /*!
         * @brief Specifies the roles for an accessibility object.
         *
         * @since BlackBerry 10.2.0
         */
        enum Type
        {
            /*! 
             * @brief The accessibility object acts as an activity indicator.
             *
             * @since BlackBerry 10.2.0
             */
            ActivityIndicator = 0,
            /*! 
             * @brief The accessibility object acts as an alert.
             *
             * @since BlackBerry 10.2.0
             */
            Alert = 1,
            /*! 
             * @brief The accessibility object acts as an alert dialog.
             *
             * @since BlackBerry 10.2.0
             */
            AlertDialog  = 2,
            /*! 
             * @brief The accessibility object acts as an article.
             *
             * @since BlackBerry 10.2.0
             */
            Article  = 4,
            /*! 
             * @brief The accessibility object acts as a banner.
             *
             * @since BlackBerry 10.2.0
             */
            Banner  = 5,
            /*! 
             * @brief The accessibility object acts as a button.
             *
             * @since BlackBerry 10.2.0
             */
            Button  = 6,
            /*! 
             * @brief The accessibility object acts as a check box.
             *
             * @since BlackBerry 10.2.0
             */
            CheckBox  = 7,
            /*! 
             * @brief The accessibility object acts as a column header.
             *
             * @since BlackBerry 10.2.0
             */
            ColumnHeader  = 8,
            /*! 
             * @brief The accessibility object acts as a combo box.
             *
             * @since BlackBerry 10.2.0
             */
            ComboBox  = 9,
            /*! 
             * @brief The accessibility object acts as a complementary.
             *
             * @since BlackBerry 10.2.0
             */
            Complementary  = 10,
            /*! 
             * @brief The accessibility object acts as a container.
             *
             * @since BlackBerry 10.2.0
             */
            Container  = 11,
            /*! 
             * @brief The accessibility object acts as content info.
             *
             * @since BlackBerry 10.2.0
             */
            ContentInfo  = 12,
            /*! 
             * @brief The accessibility object acts as a date/time picker.
             *
             * @since BlackBerry 10.2.0
             */
            DateTimePicker  = 13,
            /*! 
             * @brief The accessibility object acts as a definition.
             *
             * @since BlackBerry 10.2.0
             */
            Definition  = 14,
            /*! 
             * @brief The accessibility object acts as a dialog.
             *
             * @since BlackBerry 10.2.0
             */
            Dialog  = 15,
            /*! 
             * @brief The accessibility object acts as a directory.
             *
             * @since BlackBerry 10.2.0
             */
            Directory  = 16,
            /*! 
             * @brief The accessibility object acts as a document.
             *
             * @since BlackBerry 10.2.0
             */
            Document  = 17,
            /*! 
             * @brief The accessibility object acts as a drop-down list.
             *
             * @since BlackBerry 10.2.0
             */
            DropDown  = 18,
            /*! 
             * @brief The accessibility object acts as a form.
             *
             * @since BlackBerry 10.2.0
             */
            Form  = 19,
            /*! 
             * @brief The accessibility object acts as a grid.
             *
             * @since BlackBerry 10.2.0
             */
            Grid  = 20,
            /*! 
             * @brief The accessibility object acts as a grid cell.
             *
             * @since BlackBerry 10.2.0
             */
            GridCell  = 21,
            /*! 
             * @brief The accessibility object acts as a group.
             *
             * @since BlackBerry 10.2.0
             */
            Group  = 22,
            /*! 
             * @brief The accessibility object acts as a heading.
             *
             * @since BlackBerry 10.2.0
             */
            Heading  = 23,
            /*! 
             * @brief The accessibility object acts as an image.
             *
             * @since BlackBerry 10.2.0
             */
            Img  = 24,
            /*! 
             * @brief The accessibility object acts as a label.
             *
             * @since BlackBerry 10.2.0
             */
            Label  = 25,
            /*! 
             * @brief The accessibility object acts as a link.
             *
             * @since BlackBerry 10.2.0
             */
            Link  = 26,
            /*! 
             * @brief The accessibility object acts as a list.
             *
             * @since BlackBerry 10.2.0
             */
            List  = 27,
            /*! 
             * @brief The accessibility object acts as a list box.
             *
             * @since BlackBerry 10.2.0
             */
            ListBox  = 28,
            /*! 
             * @brief The accessibility object acts as a list item.
             *
             * @since BlackBerry 10.2.0
             */
            ListItem  = 29,
            /*! 
             * @brief The accessibility object acts as a log.
             *
             * @since BlackBerry 10.2.0
             */
            Log  = 30,
            /*! 
             * @brief The accessibility object acts as a main.
             *
             * @since BlackBerry 10.2.0
             */
            Main  = 31,
            /*! 
             * @brief The accessibility object acts as a marquee.
             *
             * @since BlackBerry 10.2.0
             */
            Marquee  = 32,
            /*! 
             * @brief The accessibility object acts as a math.
             *
             * @since BlackBerry 10.2.0
             */
            Math  = 33,
            /*! 
             * @brief The accessibility object acts as a menu.
             *
             * @since BlackBerry 10.2.0
             */
            Menu  = 34,
            /*! 
             * @brief The accessibility object acts as a menu bar.
             *
             * @since BlackBerry 10.2.0
             */
            MenuBar = 35,
            /*! 
             * @brief The accessibility object acts as a menu item.
             *
             * @since BlackBerry 10.2.0
             */
            MenuItem = 36,
            /*! 
             * @brief The accessibility object acts as a menu item check box.
             *
             * @since BlackBerry 10.2.0
             */
            MenuItemCheckBox = 37,
            /*! 
             * @brief The accessibility object acts as a menu item radio button.
             *
             * @since BlackBerry 10.2.0
             */
            MenuItemRadio = 38,
            /*! 
             * @brief The accessibility object acts as a navigation.
             *
             * @since BlackBerry 10.2.0
             */
            Navigation = 39,
            /*! 
             * @brief The accessibility object acts as a navigation pane.
             *
             * @since BlackBerry 10.2.0
             */
            NavigationPane = 40,
            /*! 
             * @brief The accessibility object acts as a note.
             *
             * @since BlackBerry 10.2.0
             */
            Note = 41,
            /*! 
             * @brief The accessibility object acts as an option item.
             *
             * @since BlackBerry 10.2.0
             */
            Option = 42,
            /*! 
             * @brief The accessibility object acts as a page.
             *
             * @since BlackBerry 10.2.0
             */
            Page = 43,
            /*! 
             * @brief The accessibility object acts as a presentation.
             *
             * @since BlackBerry 10.2.0
             */
            Presentation = 44,
            /*! 
             * @brief The accessibility object acts as a progress bar.
             *
             * @since BlackBerry 10.2.0
             */
            ProgressBar = 45,
            /*! 
             * @brief The accessibility object acts as a radio button.
             *
             * @since BlackBerry 10.2.0
             */
            Radio = 46,
            /*! 
             * @brief The accessibility object acts as a radio group.
             *
             * @since BlackBerry 10.2.0
             */
            RadioGroup = 47,
            /*! 
             * @brief The accessibility object acts as a region.
             *
             * @since BlackBerry 10.2.0
             */
            Region = 48,
            /*! 
             * @brief The accessibility object acts as a row.
             *
             * @since BlackBerry 10.2.0
             */
            Row = 49,
            /*! 
             * @brief The accessibility object acts as a row group.
             *
             * @since BlackBerry 10.2.0
             */
            RowGroup = 50,
            /*! 
             * @brief The accessibility object acts as a row header.
             *
             * @since BlackBerry 10.2.0
             */
            RowHeader = 51,
            /*! 
             * @brief The accessibility object acts as a scroll bar.
             *
             * @since BlackBerry 10.2.0
             */
            ScrollBar = 52,
            /*! 
             * @brief The accessibility object acts as a scroll view.
             *
             * @since BlackBerry 10.2.0
             */
            ScrollView = 53,
            /*! 
             * @brief The accessibility object acts as a search field.
             *
             * @since BlackBerry 10.2.0
             */
            Search = 54,
            /*! 
             * @brief The accessibility object acts as a separator.
             *
             * @since BlackBerry 10.2.0
             */
            Separator = 55,
            /*! 
             * @brief The accessibility object acts as a slider.
             *
             * @since BlackBerry 10.2.0
             */
            Slider = 56,
            /*! 
             * @brief The accessibility object acts as a spin button.
             *
             * @since BlackBerry 10.2.0
             */
            SpinButton = 57,
            /*! 
             * @brief The accessibility object acts as a status bar.
             *
             * @since BlackBerry 10.2.0
             */
            Status = 58,
            /*! 
             * @brief The accessibility object acts as a tab.
             *
             * @since BlackBerry 10.2.0
             */
            Tab = 59,
            /*! 
             * @brief The accessibility object acts as a tab list.
             *
             * @since BlackBerry 10.2.0
             */
            TabList = 60,
            /*! 
             * @brief The accessibility object acts as a tab panel.
             *
             * @since BlackBerry 10.2.0
             */
            TabPanel = 61,
            /*! 
             * @brief The accessibility object acts as a text box.
             *
             * @since BlackBerry 10.2.0
             */
            TextBox = 62,
            /*! 
             * @brief The accessibility object acts as a timer.
             *
             * @since BlackBerry 10.2.0
             */
            Timer = 63,
            /*! 
             * @brief The accessibility object acts as a toggle button.
             *
             * @since BlackBerry 10.2.0
             */
            ToggleButton = 64,
            /*! 
             * @brief The accessibility object acts as a tool bar.
             *
             * @since BlackBerry 10.2.0
             */
            ToolBar = 65,
            /*! 
             * @brief The accessibility object acts as a tool tip.
             *
             * @since BlackBerry 10.2.0
             */
            ToolTip = 66,
            /*! @brief The accessibility object acts as a tree.
             *
             * @since BlackBerry 10.2.0
             */
            Tree = 67,
            /*! @brief The accessibility object acts as a tree grid.
             *
             * @since BlackBerry 10.2.0
             */
            TreeGrid = 68,
            /*! @brief The accessibility object acts as a tree item.
             *
             * @since BlackBerry 10.2.0
             */
            TreeItem = 69,
            /*! 
             * @brief The accessibility object acts as a web view.
             *
             * @since BlackBerry 10.2.0
             */
            WebView = 70,
            /*! 
             * @brief The accessibility object's role is unknown.
             *
             * @since BlackBerry 10.2.0
             */
            Unknown = 71,
            /*! 
             * @brief The accessibility object acts as an accessibility bridge socket.
             *
             * @since BlackBerry 10.2.0
             */
            Socket = 72,
            /*! 
             * @brief The accessibility object acts as an accessibility bridge plug.
             *
             * @since BlackBerry 10.2.0
             */
            Plug = 73,
            /*! 
             * @brief The accessibility object acts as static text.
             *
             * @since BlackBerry 10.2.0
             */
            StaticText = 74,
            /*! @brief The accessibility object has an extended role.
             *
             * @see CustomA11yObject::extendedRole
             * @since BlackBerry 10.3.0
             */
            Extended = 75
        };

    private:
        /*! @cond PRIVATE */
        A11yRole();
        ~A11yRole();
        /*! @endcond */
    };
  }
}

#endif // cascades_a11yrole_h

