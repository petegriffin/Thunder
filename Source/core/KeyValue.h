#ifndef __KEYVALUE_H
#define __KEYVALUE_H

#include "Module.h"
#include "Portability.h"

namespace WPEFramework {
namespace Core {

    template <typename KEY, typename VALUE>
    class KeyValueType {
    private:
        KeyValueType();

    public:
        KeyValueType(const KEY& request)
            : m_Key(request)
            , m_Value()
        {
        }
        KeyValueType(const KEY& request, const VALUE& value)
            : m_Key(request)
            , m_Value(value)
        {
        }
        KeyValueType(KeyValueType<KEY, VALUE>& copy)
            : m_Key(copy.m_Key)
            , m_Value(copy.m_Value)
        {
        }
        ~KeyValueType()
        {
        }

        KeyValueType<KEY, VALUE>& operator=(const KeyValueType<KEY, VALUE>& RHS)
        {
            m_Key = RHS.m_Key;
            m_Value = RHS.m_Value;

            return (*this);
        }

    public:
        inline bool operator==(const KeyValueType<KEY, VALUE>& RHS) const
        {
            return ((RHS.m_Key == m_Key) && (RHS.m_Value == m_Value));
        }

        inline bool operator!=(const KeyValueType<KEY, VALUE>& RHS) const
        {
            return (!operator==(RHS));
        }

        inline KEY& Key()
        {
            return (m_Key);
        }

        inline const KEY& Key() const
        {
            return (m_Key);
        }

        inline VALUE& Value()
        {
            return (m_Value);
        }

        inline const VALUE& Value() const
        {
            return (m_Value);
        }

        inline bool IsKey(const KEY& key) const
        {
            return (key == m_Key);
        }

    private:
        KEY m_Key;
        VALUE m_Value;
    };

    template <const bool KEY_CASESENSITIVE, typename VALUE>
    class TextKeyValueType : public KeyValueType<TextFragment, VALUE> {
    public:
        TextKeyValueType()
            : KeyValueType<TextFragment, VALUE>(TextFragment(_T("")))
        {
        }
        TextKeyValueType(const TextFragment& key, const VALUE& value)
            : KeyValueType<TextFragment, VALUE>(key, value)
        {
        }
        TextKeyValueType(const TextKeyValueType<KEY_CASESENSITIVE, VALUE>& copy)
            : KeyValueType<TextFragment, VALUE>(copy)
        {
        }
        ~TextKeyValueType()
        {
        }

        TextKeyValueType<KEY_CASESENSITIVE, VALUE>& operator=(const TextKeyValueType<KEY_CASESENSITIVE, VALUE>& RHS)
        {
            KeyValueType<TextFragment, VALUE>::operator=(RHS);

            return (*this);
        }

        inline bool operator==(const TextKeyValueType<KEY_CASESENSITIVE, VALUE>& RHS) const
        {
            return (KeyValueType<TextFragment, VALUE>::operator==(RHS));
        }

        inline bool operator!=(const TextKeyValueType<KEY_CASESENSITIVE, VALUE>& RHS) const
        {
            return (KeyValueType<TextFragment, VALUE>::operator!=(RHS));
        }

        inline bool HasKey() const
        {
            return (KeyValueType<TextFragment, VALUE>::Key().IsEmpty() == false);
        }

        inline bool IsKey(const TextFragment& key) const
        {
            return (KEY_CASESENSITIVE == true ? KeyValueType<TextFragment, VALUE>::IsKey(key) : key.EqualText(KeyValueType<TextFragment, VALUE>::Key()));
        }
    };
}
} // namespace Core

#endif // __KEYVALUE_H
