import kotlin.time.*

/*
private const val MOD = 998244353

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
private fun List<ModInt>.toModIntArray() = ModIntArray(size) { get(it) }

private fun solve(n: Int) {
    val fs = (1..(1 shl n)).runningFold(ModInt(1)) { acc, i -> acc * ModInt(i) }.toModIntArray()
    val ifs = ModIntArray(fs.size) { ModInt(1) / fs[it] }
    fun cnk(n: Int, k: Int) = fs[n] * ifs[k] * ifs[n - k]
    var ans = ModIntArray(1) { ModInt(1) }
    for (round in 1..n) {
        ans = ModIntArray(ans.size * 2) {
            var x = ModInt(0)
            for (i in maxOf(it - ans.size, 0) until minOf(ans.size, it)) {
                x += ans[i] * cnk(it - 1, i) * cnk(2 * ans.size - it - 1, ans.size - i - 1)
            }
            x * ModInt(2) * fs[ans.size]
        }
    }
    println((0 until ans.size).joinToString("\n") { ans[it].x.toString() })
}



@OptIn(ExperimentalTime::class)
fun main() {
    while (true) {
            solve(readlnOrNull()?.toInt() ?: return)
    }
}
*/

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }