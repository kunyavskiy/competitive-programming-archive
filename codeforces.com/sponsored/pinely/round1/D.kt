private const val MOD = 1000000007 // 998244353

@JvmInline
@Suppress("NOTHING_TO_INLINE")
private value class ModInt(val x: Int) {
    inline operator fun plus(other: ModInt) = ModInt((x + other.x).let { if (it >= MOD) it - MOD else it })
    inline operator fun minus(other: ModInt) = ModInt((x - other.x).let { if (it < 0) it + MOD else it })
    inline operator fun times(other: ModInt) = ModInt((x.toLong() * other.x % MOD).toInt())
    fun power(p_: Int): ModInt {
        if (p_ < 0) return ModInt(0)
        var a = this
        var res = ModInt(1)
        var p = p_
        while (p != 0) {
            if ((p and 1) == 1) res *= a
            a *= a
            p = p shr 1
        }
        return res
    }

    inline operator fun div(other: ModInt) = this * other.inv()
    inline fun inv() = power(MOD - 2)

    companion object {
        inline fun from(x: Int) = ModInt((x % MOD + MOD) % MOD)
        inline fun from(x: Long) = ModInt(((x % MOD).toInt() + MOD) % MOD)
    }
}

@JvmInline
private value class ModIntArray(private val storage:IntArray) {
    operator fun get(index: Int) = ModInt(storage[index])
    operator fun set(index: Int, value: ModInt) { storage[index] = value.x }
    val size get() = storage.size
}
private inline fun ModIntArray(n: Int, init: (Int) -> ModInt) = ModIntArray(IntArray(n) { init(it).x })

private const val COMB_MAX = 2_000_000
private val fs = ModIntArray(COMB_MAX) { ModInt(1) }.apply {
    for (i in 1 until size) {
        set(i, get(i - 1) * ModInt.from(i))
    }
}
private val ifs = ModIntArray(COMB_MAX) { fs[it].inv() }

private fun cnk(n: Int, k: Int) = if (k < 0 || n < k) ModInt(0) else fs[n] * ifs[k] * ifs[n - k]


fun main() {
    while (true) {
        val (n, k) = (readlnOrNull() ?: break).split(" ").map { it.toInt() }
        var ans = ModInt(0)
        if (k == 0) {
            ans += ModInt(3).power(n)
        }
        for (g in 1..k) {
            run {
                // last is chosen
                // ...xxx...xxx...xxx|
                val ways = cnk(n - k, g - 1) * cnk(k - 1, g - 1)
                ans += ways * ModInt(3).power((n - k - g + 1) + (k - g))
            }
            run {
                // last is not chosen
                // ...xxx...xxx...xxx...|
                val ways = cnk(n - k, g) * cnk(k - 1, g - 1)
                ans += ways * ModInt(3).power((n - k - g) + (k - g))
            }
        }
        println(ans.x)
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }