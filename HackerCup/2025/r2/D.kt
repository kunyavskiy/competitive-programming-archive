import java.io.File
import java.math.BigInteger
import kotlin.time.measureTime

private const val MOD = 998_244_353

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
        inline fun from(x: BigInteger) = ModInt(((x % MOD.toBigInteger()).toInt() + MOD) % MOD)
    }
}

@JvmInline
private value class ModIntArray(val storage:IntArray) {
    inline operator fun get(index: Int) = ModInt(storage[index])
    inline operator fun set(index: Int, value: ModInt) { storage[index] = value.x }
    val size get() = storage.size
}
private inline fun ModIntArray(n: Int, init: (Int) -> ModInt) = ModIntArray(IntArray(n) { init(it).x })

private val ddp = Array(26) { k -> Array(k+1) { ModIntArray(IntArray(1 shl k) { -1 }) } }


private fun solve() {
    val (l, r, k_) = readStrings()
    val k = k_.toInt()

    val dp = ddp[k]

    fun shift(mask: Int, i: Int) : Int {
        return ((mask shl i) or (mask shr (k - i))) and ((1 shl k) - 1)
    }
    fun next(mask: Int, i: Int) = shift(mask, i % k)

    fun getDp(mask: Int, more: Int) : ModInt {
        if (more == 0) return ModInt(1)
        if (more > k) return ModInt(0)
        val oldR = dp[more].storage[mask]
        if (oldR != -1) return ModInt(oldR)
        var ans = ModInt(0)
        for (i in 1 until 10) {
            val nmaskShift = next(mask, i)
            if ((nmaskShift and 1) != 0) continue
            ans += getDp(nmaskShift or 1, more - 1)
        }
        dp[more][mask] = ans
        return ans
    }

    fun solveOne(s: String) : ModInt {
        var curMask = 1
        var ans = ModInt(0)
        for (i in 1 until s.length) {
            for (c in 1..9) {
                val nmask = next(curMask, c)
                if (nmask and 1 != 0) continue
                ans += getDp(nmask or 1, i - 1)
            }
        }
        for ((index, c) in s.withIndex()) {
            val cdigit = c.digitToInt()
            for (dgt in 1 until cdigit) {
                val nmask = next(curMask, dgt)
                if (nmask and 1 != 0) continue
                ans += getDp(nmask or 1, s.length - index - 1)
            }
            curMask = next(curMask, cdigit)
            if (cdigit == 0 || (curMask and 1) != 0) {
                return ans
            }
            curMask = curMask or 1
        }
        ans += ModInt.from(1)
        return ans;
    }

    val ans = ModInt.from(r.toBigInteger() - l.toBigInteger() + 1.toBigInteger()) - (solveOne(r) - solveOne((l.toBigInteger() - BigInteger.ONE).toString()))
    println(ans.x)
}

fun main() {
    val log = File("log.txt").printWriter()
    repeat(readInt()) {
        val time = measureTime {
            print("Case #${it + 1}: ")
            solve()
        }
        log.println("Test = ${it+1}, time=$time")
        log.flush()
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }