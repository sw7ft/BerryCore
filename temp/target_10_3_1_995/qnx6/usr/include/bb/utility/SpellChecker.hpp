/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_UTILITY_SPELLCHECKER_HPP
#define BB_UTILITY_SPELLCHECKER_HPP

#include <bb/utility/Global>

#include <QObject>
#include <QScopedPointer>
#include <QStringList>

namespace bb
{
namespace utility
{
class SpellCheckerPrivate;

/*!
 * @headerfile SpellChecker.hpp <bb/utility/SpellChecker>
 *
 * @brief Verifies the spelling of words and offers spelling suggestions.
 *
 * @details The @c %SpellChecker class uses the system spell check and the current
 * system locale to verify spelling and providing suggestions.
 * 
 * Here's an example of how to implement functions that use @c %SpellChecker to
 * check the spelling of a word and return a list of spelling suggestions:
 *
 * @code
 * bool checkSpelling(QStringList const & words)
 * {
 *     bool res = true;
 *     bb::utility::SpellChecker spellChecker;
 *     Q_FOREACH(QString const & word, words) {
 *         res = res && spellChecker.checkWord(word);
 *     }
 *     return res;
 * }
 *
 * QStringList getSomeSuggestions(QString const & word)
 * {
 *     bb::utility::SpellChecker spellChecker;
 *     return spellChecker.suggestions(word, 5);
 * }
 * @endcode
 *
 * When using a @c TextArea or @c TextField, spell check can be enabled by default
 * on text that's provided by the user, depending on the input mode that's used.
 * The input modes for a @c %TextArea and @c %TextField are specified using the
 * @c TextAreaInputMode and @c TextFieldInputMode classes, respectively.
 *
 * @xmlonly
 * <apigrouping group="Platform/Language"/>
 * <library name="bbutility"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_UTILITY_EXPORT SpellChecker : public QObject
{
    Q_OBJECT

public:
    /*!
     * @brief Creates a new instance of the @c %SpellChecker class.
     *
     * @param parent The parent of the instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit SpellChecker(QObject *parent = 0);
    
    /*!
     * @brief Destroys this @c %SpellChecker instance.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SpellChecker();

    /*!
     * @brief Checks whether the specified word is spelled correctly.
     *
     * @details The check is performed based on the current system locale.
     *
     * @param word The word to be checked.
     * @param ok If not specified, @c ok is set to @c true if the check completed
     *        successfully, and @c false otherwise (for example, on a timeout).
     * @param millisecondTimeout The maximum time, in milliseconds, to wait for an
     *        answer from the service.
     *
     * @return @c true if the @c word is spelled correctly, @c false otherwise. This
     *         function also returns @c false if an error occurred. You can use the
     *         @c ok parameter to check for errors.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bool checkWord(const QString &word, bool *ok = 0, int millisecondTimeout = 1000);

    /*!
     * @brief Retrieves spelling suggestions for the specified word.
     *
     * @details The number of results can be limited by specifying a limit.
     *
     * The check is performed based on the current system locale.
     *
     * @param word The word to be checked.
     * @param limit The maximum number of results to return. If @c 0 or less, the
     *        limit is ignored.
     * @param ok If not specified, @c ok is set to @c true if the check completed
     *        successfully, and @c false otherwise (for example, on a timeout).
     * @param millisecondTimeout The maximum time, in milliseconds, to wait for an
     *        answer from the service.
     * 
     * @return A list of spelling suggestions for the specified word. Returns an
     *         empty list if an error occurred. You can use the @c ok parameter to
     *         check for errors.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE QStringList suggestions(const QString &word, int limit = 0, bool *ok = 0, int millisecondTimeout = 1000);

private:
    Q_DISABLE_COPY(SpellChecker)
    Q_DECLARE_PRIVATE(SpellChecker)
    QScopedPointer<SpellCheckerPrivate> d_ptr;
};

} // namespace utility
} // namespace bb

#endif // BB_UTILITY_SPELLCHECKER_HPP
