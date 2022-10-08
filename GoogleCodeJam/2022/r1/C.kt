@JvmInline
value class ModInt(val x:Int) {
    operator fun plus(other: ModInt) = ModInt((x + other.x).let { if (it >= MOD) it - MOD else it })
    operator fun minus(other: ModInt) = ModInt((x - other.x).let { if (it < 0) it + MOD else it })
    operator fun times(other: ModInt) = ModInt((x.toLong() * other.x % MOD).toInt())
    fun power(p_: Int) : ModInt {
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
    fun inv() = power(MOD - 2)
    operator fun div(other: ModInt) = this * other.inv()

    companion object {
        const val MOD = 1_000_000_007
    }
}

@JvmInline
value class ModIntArray(private val storage:IntArray) {
    operator fun get(index: Int) = ModInt(storage[index])
    operator fun set(index: Int, value: ModInt) { storage[index] = value.x }
    val size get() = storage.size
}
inline fun ModIntArray(n: Int, init: (Int) -> ModInt) = ModIntArray(IntArray(n) { init(it).x })

private fun solve() {
    val (n, k) = readInts()
    val dp = ModIntArray(n + 1) { ModInt(0) }
    dp[n - 2] = ModInt(1)
    val c1 = ModIntArray(n + 1) { ModInt(2 * (n - it)) / ModInt(2 * n - it - 1) }
    val c2 = ModIntArray(n + 1) { ModInt(2 * (it - 1)) / ModInt(2 * n - it - 1) }
    for (j in 1 until n - k) {
        for (i in 0 .. n - 2) {
            if (i >= 1) { dp[i - 1] += dp[i] * c1[i] }
            if (i >= 2) { dp[i - 2] += dp[i] * c2[i] }
            dp[i] = ModInt(0)
        }
    }
    println(dp[0].x)
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