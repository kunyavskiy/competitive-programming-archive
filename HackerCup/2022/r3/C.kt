import kotlin.random.*

@JvmInline
private value class EncodedLong(val x: Long) {
    val f get() = (x shr 32).toInt()
    val s get() = (x and ((1L shl 32) - 1)).toInt()

    constructor(a: Int, b: Int) : this((a.toLong() shl 32) or b.toLong())

    operator fun plus(other: EncodedLong) = EncodedLong(addMod(f, other.f, MOD1), addMod(s, other.s, MOD2))
    operator fun minus(other: EncodedLong) = EncodedLong(subMod(f, other.f, MOD1), subMod(s, other.s, MOD2))
    operator fun times(other: EncodedLong) =
        EncodedLong((f.toLong() * other.f.toLong() % MOD1).toInt(), (s.toLong() * other.s.toLong() % MOD2).toInt())

    companion object {
        private const val P1 = 12345678
        private const val P2 = 98654321
        private const val MOD1 = 1000000007
        private const val MOD2 = 1000000009
        val P = EncodedLong(P1, P2)

        private inline fun addMod(a: Int, b: Int, mod: Int): Int {
            val c = a + b
            return if (c >= mod) c - mod else c
        }

        private inline fun subMod(a: Int, b: Int, mod: Int): Int {
            val c = a - b
            return if (c < 0) c + mod else c
        }

        private inline fun prefixSumArray(size: Int, elem: (Int) -> EncodedLong) =
            EncodedLongArray(size + 1) { EncodedLong(0) }.apply {
                for (i in 0 until size) {
                    set(i + 1, get(i) * P + elem(i))
                }
            }
    }
}

@JvmInline
private value class EncodedLongArray(private val storage: LongArray) {
    operator fun get(index: Int) = EncodedLong(storage[index])
    operator fun set(index: Int, value: EncodedLong) {
        storage[index] = value.x
    }

    val size get() = storage.size
}
private fun EncodedLongArray(n: Int, init: (Int) -> EncodedLong) = EncodedLongArray(LongArray(n) { init(it).x })

private fun solve() {
    fun String.toCodes() = IntArray(length) {
        when (get(it)) {
            'm' -> 1
            'e' -> 2
            't' -> 3
            'a' -> 4
            else -> TODO()
        }
    }
    val a = List(readInt()) { readLn().toCodes() }
    val b = List(readInt()) { readLn().toCodes() }
    val L = a[0].size
    val degs = EncodedLongArray(L) { EncodedLong(1, 1) }.apply {
        for (i in 1 until size) {
            set(i, get(i - 1) * EncodedLong.P)
        }
    }

    val originals = mutableMapOf<EncodedLong, Int>()
    val oneError = mutableMapOf<EncodedLong, Int>()
    val oneErrorWild = mutableMapOf<EncodedLong, Int>()
    fun MutableMap<EncodedLong, Int>.inc(h: EncodedLong) = set(h, getOrDefault(h, 0) + 1)
    for (s in a) {
        var hash = EncodedLong(0, 0)
        for (it in s.indices) {
            hash += EncodedLong(s[it], s[it]) * degs[it]
        }
        originals.inc(hash)
        for (it in s.indices) {
            oneErrorWild.inc(hash + (EncodedLong(5, 5) - EncodedLong(s[it], s[it])) * degs[it])
            for (o in 1 until 5) {
                if (o != s[it])
                    oneError.inc(hash + (EncodedLong(o, o) - EncodedLong(s[it], s[it])) * degs[it])
            }
        }
    }

    var ans = 0L

    for (s in b) {
        var hash = EncodedLong(0, 0)
        for (it in s.indices) {
            hash += EncodedLong(s[it], s[it]) * degs[it]
        }
        ans -= L.toLong() * originals.getOrDefault(hash, 0).toLong()
        for (it in s.indices) {
            ans -= 2 * oneErrorWild.getOrDefault(hash + (EncodedLong(5, 5) - EncodedLong(s[it], s[it])) * degs[it], 0).toLong()
            for (o in 1 until 5) {
                if (o != s[it]) {
                    ans += oneError.getOrDefault(hash + (EncodedLong(o, o) - EncodedLong(s[it], s[it])) * degs[it], 0).toLong()
                }
            }
        }
    }
    require(ans % 2L == 0L)
    println(ans / 2L)
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }