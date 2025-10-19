private const val MOD =  1000000007 // 998244353

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

private fun divs(b_: Long): Map<Long, Int> {
    var b = b_
    var i = 2L
    return buildMap {
        while (i * i <= b) {
            if (b % i == 0L) {
                var d = 0
                while (b % i == 0L) {
                    b /= i
                    d++
                }
                put(i, d)
            }
            i++
        }
        if (b > 1) put(b, 1)
    }
}


private fun cnk(n: Long, k: Int): ModInt {
    var res = ModInt.from(1)
    for (i in 1..k) res *= ModInt.from(n - i + 1) / ModInt.from(i)
    return res
}
private fun cnkr(n: Long, k: Int) = cnk(n+k-1, k)

private fun solve() {
    val (n, a, b) = readLongs()
    val d = divs(b)
    val kd = d.keys.toList()

    var ans = ModInt.from(0)
    fun go(index: Int, cura: Long, count: ModInt) {
        if (cura > a) return
        if (index == kd.size) {
            ans += count
            return
        }
        val p = kd[index]
        val lim = d[p]!!
        var ccura = cura
        for (i in 0..lim) {
            go(index + 1, ccura, count * cnkr(n, i) * cnkr(n, lim - i))
            ccura *= p
        }
    }
    go(0, 1, ModInt.from(1))
    println(ans.x)
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