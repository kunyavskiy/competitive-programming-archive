import kotlin.math.*

private const val MOD = 1000000007
@JvmInline
private value class ModInt(val x:Int) {
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
    operator fun div(other: ModInt) = this * other.power(MOD - 2)
}

private fun norm(x: Int) = ModInt((x % MOD + MOD) % MOD)

@JvmInline
private value class ModIntArray(private val storage:IntArray) {
    operator fun get(index: Int) = ModInt(storage[index])
    operator fun set(index: Int, value: ModInt) { storage[index] = value.x }
    fun getOrZero(index: Int) = if (index > storage.size) ModInt(0) else get(index)
    val size get() = storage.size
}
private inline fun ModIntArray(n: Int, init: (Int) -> ModInt) = ModIntArray(IntArray(n) { init(it).x })
private fun List<ModInt>.toModIntArray() = ModIntArray(size) { get(it) }

private fun calc(vals: IntArray) : List<ModIntArray> {
    val ans = List(vals.size + 1) { ModIntArray(vals.size + 1) { ModInt(0) } }
    ans[0][0] = ModInt(1)
    for (i in 1 until vals.size) {
        for (j in vals.indices) {
            ans[i][j] = ans[i - 1][j]
            if (j != 0) ans[i][j] = ans[i][j] + ans[i - 1][j - 1] * norm(vals[i])
        }
    }
    return ans
}


fun main() {
    val (_, k) = readInts()
    val a = readInts()
    val ag = a.groupBy { it.sign }
    val negs = ag[-1]!!.sorted().toIntArray()
    val poss = ag[1]!!.sortedDescending().toIntArray()
    val zs = ag[0]!!.size

    val dpp = calc(poss)
    val dpn = calc(negs)
    val dpa = calc(a.toIntArray())

    var ans = ModInt(0)
    for (i in dpp.indices) {
        ans += dpp[i].getOrZero(k) * (ModInt(2).power(dpp.size - i + zs) - ModInt(1))
    }
    if (k % 2 == 0) {
        for (i in dpn.indices) {
            ans += dpn[i].getOrZero(k) * (ModInt(2).power(dpn.size - i + zs) - ModInt(1))
        }
    } else {
        val dpnr = calc(negs.reversedArray())
        for (i in dpn.indices) {
            ans += dpnr[i].getOrZero(k) * (ModInt(2).power(dpnr.size - i) - ModInt(1))
        }
    }
    ans += dpa.last().getOrZero(k)

    for (pi in poss.indices) {
        for (ni in negs.indices) {
            val coefPos = ModInt(poss[pi]) * ModInt(negs[ni]) * (ModInt(2).power(poss.size - pi - 1 + negs.size - ni - 1 + zs) - ModInt(1))
            var coefNeg = ModInt(0)
            for (ri in pi + 1 until poss.size) {
                coefNeg += ModInt(poss[pi]) * ModInt(poss[ri]) * ModInt(2).power(poss.size - pi - 1 + negs.count { it.toLong() * negs[ni] <= poss[ri].toLong() * poss[pi] } + zs)
            }
            for (ri in ni + 1 until negs.size) {
                coefNeg += ModInt(negs[ni]) * ModInt(negs[ri]) * ModInt(2).power(negs.size - ni - 1 + poss.count { poss[pi].toLong() * negs[ni] <= poss[ri].toLong() * poss[pi] } + zs)
            }
            for (cntp in 0 until pi) {
                val cntn = k - cntp - 2
                if (cntn >= ni || cntn < 0) continue
                ans += dpp[pi][cntp] * dpn[ni][cntn] * if (cntn % 2 == 1) coefNeg else coefPos
            }
        }
    }
    println(ans)
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }