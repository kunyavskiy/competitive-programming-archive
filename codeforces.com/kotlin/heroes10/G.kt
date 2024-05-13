private const val MOD =  1000000007

@JvmInline
@Suppress("NOTHING_TO_INLINE")
private value class ModInt(val x: Int) {
    inline operator fun plus(other: ModInt) = ModInt((x + other.x).let { if (it >= MOD) it - MOD else it })
    inline operator fun minus(other: ModInt) = ModInt((x - other.x).let { if (it < 0) it + MOD else it })
    inline operator fun times(other: ModInt) = ModInt((x.toLong() * other.x % MOD).toInt())
    fun power(p_: Int): ModInt {
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
private value class ModIntArray(val storage:IntArray) {
    operator fun get(index: Int) = ModInt(storage[index])
    operator fun set(index: Int, value: ModInt) { storage[index] = value.x }
    val size get() = storage.size
}
private inline fun ModIntArray(n: Int, init: (Int) -> ModInt) = ModIntArray(IntArray(n) { init(it).x })

private const val COMB_MAX = 400_010

private val fs = ModIntArray(COMB_MAX) { ModInt(1) }.apply {
    for (i in 1 until size) {
        set(i, get(i - 1) * ModInt.from(i))
    }
}
private val ifs = ModIntArray(COMB_MAX) { fs[it].inv() }

private fun cnk(n: Int, k: Int) = if (n >= k) fs[n] * ifs[k] * ifs[n - k] else ModInt(0)

fun main() {
    val (n, k) = readInts()
    val ans = ModIntArray(n + 1) { ModInt(0) }

    for (diff in -n..n) {
        val ways = maxOf(0, diff - 1)
        val ll = maxOf(1, diff)
        val rr = minOf(n, n - 1 + diff)
        ans[ways] += ModInt(maxOf(0, rr - ll)) * cnk(n - diff - 1, k - 2)
    }
    for (i in 1 until n) {
        ans[i] += cnk(n - i - 1, k - 1)
    }
    for (j in 0 until n - 1) {
        ans[n - j - 1] += cnk(j, k - 1)
    }
    println(ans.storage.joinToString(" "))
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }