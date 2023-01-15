private const val MOD =  998244353

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

fun main() {
    while (true) {
        val (n, q) = readlnOrNull()?.split(" ")?.map { it.toInt() } ?: break
        val p = ModInt(q) / ModInt(10000)
        val np = ModInt(1) - p

        val c11 = Array(2 * n + 7) { ModIntArray(2 * n + 7) { ModInt(0) } }
        val c12 = Array(2 * n + 7) { ModIntArray(2 * n + 7) { ModInt(0) } }

        fun fillc(c: Array<ModIntArray>) {
            for (i in 1 until c.size - 2) {
                for (j in 1 until c[i].size - 2) {
                    c[i + 2][j] += c[i][j] * ModInt(i) / ModInt(i + j)
                    c[i][j + 2] += c[i][j] * ModInt(j) / ModInt(i + j)
                }
            }
        }

        c11[1][1] = ModInt(1)
        fillc(c11)
        c12[1][2] = ModInt(1)
        fillc(c12)

        val dp = Array(n + 1) { ModIntArray(n + 1) { ModInt(0) } }
        dp[0] = ModIntArray(n + 1) { ModInt(1) }
        val dp2 = Array(n + 1) { ModIntArray(n + 1) { ModInt(0) } }
        dp2[0] = ModIntArray(n + 1) { ModInt(1) }

        for (i in 1..n) {
            for (j in 0..n - i) {
                for (inside in 0 until i) {
                    val outside = i - inside - 1
                    val ansinside = dp[inside][j + 1] * p + if (j == 0) ModInt(0) else dp[inside][j - 1] * np
                    dp[i][j] += c12[2 * inside + 1][2 * outside + 2] * dp2[outside][j] * ansinside
                }
                for (left in 0..i) {
                    val right = i - left
                    dp2[i][j] += c11[2 * left + 1][2 * right + 1] * dp[left][j] * dp[right][j]
                }
            }
        }

        println(dp[n][0].x)
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }