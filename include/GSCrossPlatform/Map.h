#ifndef GSCROSSPLATFORM_MAP_H
#define GSCROSSPLATFORM_MAP_H

#include <GSCrossPlatform/Vector.h>

template<typename KeyT, typename ValueT>
class Pair {
public:

    using KeyType = KeyT;

    using ValueType = ValueT;

public:

    constexpr Pair() = default;

    constexpr Pair(KeyType key, ValueType value)
            : _key(key), _value(value) {}

    constexpr Pair(ConstLRef<Pair<KeyType, ValueType>> pair) {
        if (this == &pair) {
            return;
        }

        _key = pair.Key();

        _value = pair.Value();
    }

    constexpr Pair(RRef<Pair<KeyType, ValueType>> pair) noexcept {
        if (this == &pair) {
            return;
        }

        _key = std::move(pair.Key());

        _value = std::move(pair.Value());
    }

public:

    inline constexpr LRef<KeyType> Key() {
        return _key;
    }

    inline constexpr LRef<ValueType> Value() {
        return _value;
    }

    inline constexpr ConstLRef<KeyType> Key() const {
        return _key;
    }

    inline constexpr ConstLRef<ValueType> Value() const {
        return _value;
    }

public:

    inline constexpr LRef<Pair<KeyType, ValueType>> operator=(ConstLRef<Pair<KeyType, ValueType>> pair) {
        if (this == &pair) {
            return *this;
        }

        _key = pair.Key();

        _value = pair.Value();

        return *this;
    }

    inline constexpr LRef<Pair<KeyType, ValueType>> operator=(RRef<Pair<KeyType, ValueType>> pair) noexcept {
        if (this == &pair) {
            return *this;
        }

        _key = std::move(pair.Key());

        _value = std::move(pair.Value());

        return *this;
    }

    inline constexpr Bool operator==(ConstLRef<Pair<KeyType, ValueType>> pair) const {
        if (_key != pair.Key() || _value != pair.Value()) {
            return false;
        }

        return true;
    }

    inline constexpr Bool operator!=(ConstLRef<Pair<KeyType, ValueType>> pair) const {
        return !(*this == pair);
    }

private:

    KeyType _key;

    ValueType _value;
};

template<typename KeyT, typename ValueT>
class Map {
public:

    using KeyType = KeyT;

    using ValueType = ValueT;

public:

    using Iterator = typename Vector<Pair<KeyType, ValueType>>::Iterator;

    using ConstIterator = typename Vector<Pair<KeyType, ValueType>>::ConstIterator;

public:

    constexpr Map() = default;

    constexpr Map(std::initializer_list<Pair<KeyType, ValueType>> initializerList) {
        for (auto &pair : initializerList) {
            _pairs.append(pair);
        }
    }

    constexpr Map(ConstLRef<Map<KeyType, ValueType>>map) {
        if (this == &map) {
            return;
        }

        _pairs = map.Pairs();
    }

    constexpr Map(RRef<Map<KeyType, ValueType>> map) noexcept {
        if (this == &map) {
            return;
        }

        _pairs = std::move(map.Pairs());
    }

public:

    inline constexpr LRef<Map<KeyType, ValueType>> Append(ConstLRef<Pair<KeyType, ValueType>> pair) {
        _pairs.Append(pair);

        return *this;
    }

    inline constexpr LRef<Map<KeyType, ValueType>> Append(std::initializer_list<Pair<KeyType, ValueType>> pairs) {
        for (auto &pair : pairs) {
            Append(pair);
        }

        return *this;
    }

public:

    inline constexpr Ptr<Pair<KeyType, ValueType>> Data() {
        return _pairs.Data();
    }

    inline constexpr U64 Size() const {
        return _pairs.Size();
    }

public:

    inline constexpr Iterator begin() {
        return _pairs.begin();
    }

    inline constexpr Iterator end() {
        return _pairs.end();
    }

    inline constexpr ConstIterator begin() const {
        return _pairs.begin();
    }

    inline constexpr ConstIterator end() const {
        return _pairs.end();
    }

    inline constexpr ConstIterator cbegin() const {
        return _pairs.cbegin();
    }

    inline constexpr ConstIterator cend() const {
        return _pairs.cend();
    }

public:

    inline constexpr LRef<Map<KeyType, ValueType>> operator=(ConstLRef<Map<KeyType, ValueType>> map) {
        if (this == &map) {
            return *this;
        }

        _pairs = map._pairs;

        return *this;
    }

    inline constexpr Map<KeyType, ValueType> &operator=(RRef<Map<KeyType, ValueType>> map) noexcept {
        if (this == &map) {
            return *this;
        }

        _pairs = std::move(map._pairs);

        return *this;
    }

    inline constexpr Bool operator==(ConstLRef<Map<KeyType, ValueType>> map) const {
        if (_pairs.Size() != map.Size()) {
            return false;
        }

        for (U64 index = 0; auto &pair : map) {
            if (_pairs[index] != pair) {
                return false;
            }
        }

        return true;
    }

    inline constexpr Bool operator!=(ConstLRef<Map<KeyType, ValueType>> map) const {
        return !(*this == map);
    }

    inline constexpr LRef<ValueType> operator[](ConstLRef<KeyType> key) {
        for (auto &pair : _pairs) {
            if (pair.Key() == key) {
                return pair.Value();
            }
        }

        return _pairs.Append(Pair<KeyType, ValueType>(key, ValueType()))[_pairs.Size() - 1].Value();
    }

    inline constexpr ConstLRef<ValueType> operator[](ConstLRef<KeyType> key) const {
        for (auto &pair : _pairs) {
            if (pair.Key() == key) {
                return pair.Value();
            }
        }

        return _pairs.Append(Pair<KeyType, ValueType>(key, ValueType()))[_pairs.Size() - 1].Value();
    }

private:

    Vector<Pair<KeyType, ValueType>> _pairs;
};

template<typename KeyT, typename ValueT>
inline constexpr Pair<KeyT, ValueT> make_pair() {
    return Pair<KeyT, ValueT>();
}

template<typename KeyT, typename ValueT>
inline constexpr Pair<KeyT, ValueT> make_pair(KeyT key, ValueT value) {
    return Pair<KeyT, ValueT>(key, value);
}

template<typename KeyT, typename ValueT>
inline constexpr Pair<KeyT, ValueT> make_pair(ConstLRef<Pair<KeyT, ValueT>> pair) {
    return Pair<KeyT, ValueT>(pair);
}

template<typename KeyT, typename ValueT>
inline constexpr Pair<KeyT, ValueT> make_pair(RRef<Pair<KeyT, ValueT>> pair) {
    return Pair<KeyT, ValueT>(pair);
}

template<typename KeyT, typename ValueT>
inline constexpr Map<KeyT, ValueT> make_map() {
    return Map<KeyT, ValueT>();
}

template<typename KeyT, typename ValueT>
inline constexpr Map<KeyT, ValueT> make_map(std::initializer_list<Pair<KeyT, ValueT>> initializerList) {
    return Map<KeyT, ValueT>(initializerList);
}

template<typename KeyT, typename ValueT>
inline constexpr Map<KeyT, ValueT> make_map(ConstLRef<Map<KeyT, ValueT>> map) {
    return Map<KeyT, ValueT>(map);
}

template<typename KeyT, typename ValueT>
inline constexpr Map<KeyT, ValueT> make_map(RRef<Map<KeyT, ValueT>> map) {
    return Map<KeyT, ValueT>(map);
}

namespace std {

    template<typename KeyT, typename ValueT>
    constexpr size_t size(ConstLRef<Map<KeyT, ValueT>> map) noexcept {
        return map.Size();
    }

    template<typename KeyT, typename ValueT>
    constexpr auto data(LRef<Map<KeyT, ValueT>> map) {
        return map.Data();
    }

    template<typename KeyT, typename ValueT>
    constexpr auto begin(LRef<Map<KeyT, ValueT>> map) {
        return map.begin();
    }

    template<typename KeyT, typename ValueT>
    constexpr auto end(LRef<Map<KeyT, ValueT>> map) {
        return map.end();
    }

    template<typename KeyT, typename ValueT>
    constexpr auto begin(ConstLRef<Map<KeyT, ValueT>> map) {
        return map.begin();
    }

    template<typename KeyT, typename ValueT>
    constexpr auto end(ConstLRef<Map<KeyT, ValueT>> map) {
        return map.end();
    }

    template<typename KeyT, typename ValueT>
    constexpr auto cbegin(ConstLRef<Map<KeyT, ValueT>> map) {
        return map.cbegin();
    }

    template<typename KeyT, typename ValueT>
    constexpr auto cend(ConstLRef<Map<KeyT, ValueT>> map) {
        return map.cend();
    }

}

#endif //GSCROSSPLATFORM_MAP_H
