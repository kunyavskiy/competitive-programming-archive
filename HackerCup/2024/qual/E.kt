import kotlin.time.ExperimentalTime
import kotlin.time.measureTime

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

private fun merge(s: CharArray, t: CharArray) : CharArray {
    val temp = CharArray(minOf(s.size, t.size))
    for (i in 0 until temp.size) {
        val s1 = s[i]
        val t1 = t[i]
        temp[i] = when {
            s1 == t1 -> s1
            s1 == '?' -> t1
            t1 == '?' -> s1
            else -> return temp.copyOfRange(0, i)
        }
    }
    return temp
}

@OptIn(ExperimentalTime::class)
private fun solve() {
    val s = List(readInt()) { readln() }
    var ans: ModInt = ModInt.from(0)
    val merged = Array<CharArray?>(1 shl s.size) { null }
    for (i in s.indices) {
        merged[1 shl i] = s[i].toCharArray()
    }
    //System.err.println(measureTime {
        for (i in 1 until (1 shl s.size)) {
            val a = i and (i - 1)
            val b = i and (i - 1).inv()
            if (a != 0 && b != 0) {
                merged[i] = merge(merged[a]!!, merged[b]!!)
            }
        }
    //})
    val alph = ModInt.from(26)
    for (mask in 1 until (1 shl s.size)) {
        var cur = ModInt.from(1)
        var pw = ModInt.from(1)
        for (ch in merged[mask]!!) {
            if (ch == '?') {
                pw = pw * alph
            }
            cur += pw
        }
        if (mask.countOneBits() % 2 == 0) {
            ans -= cur
        } else {
            ans += cur
        }
    }
    println(ans.x)
}

@OptIn(ExperimentalTime::class)
fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        val time = measureTime {
            solve()
        }
        System.err.println("${it+1} $time")
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }