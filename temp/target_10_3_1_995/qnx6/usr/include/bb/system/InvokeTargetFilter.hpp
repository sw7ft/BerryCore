/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKETARGETFILTER_HPP
#define BB_SYSTEM_INVOKETARGETFILTER_HPP

#include <bb/system/Global>

#include <QSharedDataPointer>
#include <QStringList>
#include <QMap>

namespace bb
{
namespace system
{

class InvokeTargetFilterPrivate;

/*!
 * @headerfile InvokeTargetFilter.hpp <bb/system/InvokeTargetFilter>
 *
 * @brief Describes the kinds of unbound invocations supported by a target.
 *
 * @details Through unbound invocation a target will only receive invocations
 * that match one of its filters. A filter describes the action/MIME type/URI
 * combinations for which the target supports unbound invocation.
 *
 * An invocation target filter must be specified as follows:
 * - The filter must contain at least one valid action in @c actionList(). An action can be up to 50 characters based on the following grammar:
 *    - action: \<domain\>\<sub-domain\>
 *    - domain: [a-zA-Z] ([a-zA-Z0-9_])*
 *    - sub-domain:  NUL | .\<domain\>\<sub-domain\>
 * 
 *   An example action is "bb.action.VIEW". This maps to the "actions" attribute of an Invoke-Target-Filter as defined in the BAR manifest.
 *
 * - The filter must contain at least one valid MIME type in @c mimeTypeList(). A valid MIME type is of the form:
 *    - mimetype: type subtype
 *    - type: [a-zA-Z0-9_]+
 *    - subtype: NUL | / [a-zA-Z0-9_\-\.\+]+
 * 
 *   A MIME type may include wildcards for the complete type (e.g., "*") or for the subtype only (e.g., "image/\*").
 *   The MIME type maps to the "types" attribute of an Invoke-Target-Filter as defined in the BAR manifest.
 *
 * - The filter may contain a list of URI prefixes in @c uriList() which can be used as criteria to match the URI in the invocation request (e.g., "file://",
 *   "http://localhost:port", or "file://specific/path/"). This maps to the "uris" attribute of an Invoke-Target-Filter as defined
 *   in the BAR manifest. If no URIs are specified then the in-band URI ("data://local") is implied.
 *
 * - The filter may contain a list of supported file extensions in @c fileExtensionList() that must be suffix of the path to be a match (e.g. "jpg").
 *   This maps to the @c "exts" attribute of an Invoke-Target-Filter as defined in the BAR manifest.
 * 
 *   Note that the file extensions are only applied if the scheme of the accompanying URI is "file://".  Also note that combining file extensions
 *   and specific MIME types in a filter means both must be specified by a client for the filter to match.
 *   This can also work if the extension is for a known MIME type where the invocation framework will perform type inference. However, for most cases it is best to
 *   have the "exts" filter as a separate Target-Invoke-Filter declaration in the BAR manifest file that accepts any file of any MIME type
 *   (that is, the filter should include "uris=file://;types=*;" so the only filtering criteria will be the file extensions in the "exts" attribute).
 *
 * An example of an invoke target filter, as defined in a BAR manifest, is as follows:
 *
 * Invoke-Target-Filter:actions=bb.action.OPEN;types=vnd.custom.type;uris=file://;exts=acme;
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT InvokeTargetFilter
{
public:
    /*!
     * @brief Creates a new @c InvokeTargetFilter object.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeTargetFilter();

    /*!
     * @brief Creates a copy of an existing @c InvokeTargetFilter object.
     *
     * @param other The source @c InvokeTargetFilter object to copy.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeTargetFilter(const InvokeTargetFilter &other);

    /*!
     * @brief Destroys this @c InvokeTargetFilter object.
     *
     * @since BlackBerry 10.0.0
     */
    ~InvokeTargetFilter();
    
    /*!
     * @brief Copies the data of an existing @c InvokeTargetFilter object to this object.
     *
     * @param other The source @c InvokeTargetFilter object to copy.
     *
     * @return The @c InvokeTargetFilter instance.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeTargetFilter& operator=(const InvokeTargetFilter &other);

    /*!
     * @brief Returns the list of actions.
     *
     * @return The list of actions.
     *
     * @since BlackBerry 10.0.0
     */
    QStringList actionList() const;

    /*!
     * @brief Adds an action to the action list.
     *
     * @details An action can be up to 50 characters based on the following grammar:
     *   - action: \<domain\>\<sub-domain\>
     *   - domain: [a-zA-Z] ([a-zA-Z0-9_])*
     *   - sub-domain:  NUL | .\<domain\>\<sub-domain\>
     *
     * @param action The action to add. If the action is already in the list,
     *        it is not added again.
     *
     * @return Returns @c true if the action was added; @c false otherwise.  An action is rejected if it is
     *         invalid (it is too long or does not match the grammar) or if it is already in the list.
     *
     * @since BlackBerry 10.0.0
     */
    bool addAction(const QString &action);

    /*!
     * @brief Removes an action from the action list.
     *
     * @param action The action to remove.
     *
     * @since BlackBerry 10.0.0
     */
    void removeAction(const QString &action);

    /*!
     * @brief Returns the list of MIME types.
     *
     * @return The list of MIME types.
     *
     * @since BlackBerry 10.0.0
     */
    QStringList mimeTypeList() const;

    /*!
     * @brief Adds a MIME type to the MIME type list.
     *
     * A valid MIME type is of the form:
     *   - mimeType: type subtype
     *   - type: [a-zA-Z0-9_]+
     *   - subtype: NUL | / [a-zA-Z0-9_\-\.\+]+
     *   .
     *   A MIME type may include wildcards for the complete type (e.g., "*") or for the subtype (e.g., "image/\*").
     *
     * @param mimeType The MIME type to add. If the MIME type is already in the list,
     *        it is not added again.

     * @return Returns @c true if the supplied MIME type was added to the list, @c false
     *         otherwise.  A MIME type is rejected if it is invalid (it does not match the grammar)
     *         or if it is already in the list.
     *
     * @since BlackBerry 10.0.0
     */
    bool addMimeType(const QString &mimeType);

    /*!
     * @brief Removes a MIME type from the MIME type list.
     *
     * @param mimeType The action to remove.
     *
     * @since BlackBerry 10.0.0
     */
    void removeMimeType(const QString &mimeType);

    /*!
     * @brief Returns the list of URIs.
     *
     * @return The list of URIs.
     *
     * @since BlackBerry 10.0.0
     */
    QStringList uriList() const;

    /*!
     * @brief Adds a URI to the URI list.
     *
     * @param uri A string representing the URI to add. If the URI is already in the list,
     *        it is not added again.
     *
     * @since BlackBerry 10.0.0
     */
    void addUri(const QString &uri);

    /*!
     * @brief Removes a URI from the URI list.
     *
     * @param uri A string representing the URI to remove.
     *
     * @since BlackBerry 10.0.0
     */
    void removeUri(const QString &uri);

    /*!
     * @brief Returns the list of file extensions.
     *
     * @return The list of file extensions.
     *
     * @since BlackBerry 10.0.0
     */
    QStringList fileExtensionList() const;

    /*!
     * @brief Adds a file extension to the file extension list.
     *
     * @param fileExtension The file extension to add. If the file extension is already in the list,
     *        it is not added again.
     *
     * @since BlackBerry 10.0.0
     */
    void addFileExtension(const QString &fileExtension);

    /*!
     * @brief Removes a file extension from the file extension list.
     *
     * @param fileExtension The file extension to remove.
     *
     * @since BlackBerry 10.0.0
     */
    void removeFileExtension(const QString &fileExtension);

    /*!
     * @brief Returns a list of custom attribute names of the filter.
     * @details Use @c addCustomAttributeValue() and @c removeCustomAttributeValue()to manipulate the values of the custom attributes.
     *
     * @return The list of custom attribute names.
     *
     * @since BlackBerry 10.0.0
     */
    QStringList customAttributeNames() const;

    /*!
     * @brief Returns the list of values for custom attribute @c customAttribute.
     * @details Use @c customAttributeNames() to retrieve the list of attribute names that can be used.
     *
     * @param customAttribute The name of the custom attribute for which the values are requested.
     *
     * @return The list of values for @c customAttribute.
     *
     * @since BlackBerry 10.0.0
     */
    QStringList customAttributeList(const QString &customAttribute) const;

    /*!
     * @brief Adds @c attributeValue to the list of values for custom attribute @c customAttribute.
     *
     * @details If @c attributeValue has already been added to the list for @c customAttribute,
     * it will not be added again.
     *
     * @param customAttribute The name of the custom attribute to which to add @c attributeValue.
     * @param attributeValue The value to add to the list of values for @c customAttribute.
     *
     * @since BlackBerry 10.0.0
     */
    void addCustomAttributeValue(const QString &customAttribute, const QString &attributeValue);

    /*!
     * @brief Removes @c attributeValue from the list of values for custom attribute @c customAttribute.
     *
     * @param customAttribute The name of the custom attribute from which to remove @c attributeValue.
     * @param attributeValue The value to remove from the list of values for @c customAttribute.
     *
     * @since BlackBerry 10.0.0
     */
    void removeCustomAttributeValue(const QString &customAttribute, const QString &attributeValue);

    /*!
     * @brief Removes all values associated with custom attribute @c customAttribute.
     *
     * @param customAttribute The name of the custom attribute from which to remove all attribute values.
     *
     * @since BlackBerry 10.0.0
     */
    void removeCustomAttribute(const QString &customAttribute);

    /*!
     * @brief Returns an indication of whether this instance is valid.
     *
     * @details An @c InvokeTargetFilter instance is valid if at least one action
     * has been added and at least one MIME type has been added.
     *
     * @return Returns @c true if this instance is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    /*! @cond PRIVATE */
    QSharedDataPointer<InvokeTargetFilterPrivate> d_ptr;
    friend class InvokeTargetFilterPrivate;
    /*! @endcond */
};

} // namespace system
} // namespace bb

#endif // BB_SYSTEM_INVOKETARGETFILTER_HPP
