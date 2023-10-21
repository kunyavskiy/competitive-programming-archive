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
private value class ModIntArray(private val storage:IntArray) {
    operator fun get(index: Int) = ModInt(storage[index])
    operator fun set(index: Int, value: ModInt) { storage[index] = value.x }
    val size get() = storage.size
}
private inline fun ModIntArray(n: Int, init: (Int) -> ModInt) = ModIntArray(IntArray(n) { init(it).x })

private const val COMB_MAX = 1_000_001
private val fs = ModIntArray(COMB_MAX) { ModInt(1) }.apply {
    for (i in 1 until size) {
        set(i, get(i - 1) * ModInt.from(i))
    }
}
private val ifs = ModIntArray(COMB_MAX) { fs[it].inv() }

private fun cnk(n: Int, k: Int) = fs[n] * ifs[k] * ifs[n - k]

private fun solve() {
    val (n, k, d) = readInts()
    val a = readInts().toSet()
    val max = a.max() + 1
    val ans = ModIntArray(max) {
        if (it == 0) return@ModIntArray ModInt(0)
        val count = (it until  max step it).count { it in a }
        if (count >= k)
            cnk(count, k) * fs[k]
        else
            ModInt(0)
    }
    for (i in max - 1 downTo 1) {
        for (j in (2*i) until max step i) {
            ans[i] = ans[i] - ans[j]
        }
    }
    var res = ModInt(0)
    for (i in 1 until max) {
        if (d % i == 0) {
            res += ans[i]
        }
    }
    println(res.x)
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }