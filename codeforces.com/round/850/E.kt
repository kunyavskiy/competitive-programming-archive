import kotlin.math.*
import kotlin.time.*

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
    operator fun component1() = get(0)
    operator fun component2() = get(1)
    operator fun component3() = get(2)
}
private inline fun ModIntArray(n: Int, init: (Int) -> ModInt) = ModIntArray(IntArray(n) { init(it).x })

inline fun Int.nextA() = when (this) {
    0 -> 1
    1 -> 0
    2 -> 3
    3 -> 0
    else -> TODO()
}

inline fun Int.nextB() = when (this) {
    0 -> 2
    1 -> 3
    2 -> 0
    3 -> 0
    else -> TODO()
}
fun Int.next(c: Char) = if (c == 'a') nextA() else nextB()

var mask = 0

@JvmInline
@Suppress("NOTHING_TO_INLINE")
private value class DpState(val code: Int)  {
    val p0 get() = code and 3
    val p1 get() = (code shr 2) and 3
    val p2 get() = (code shr 4) and 3
    val bal get() = (code shr 6)
    constructor(p0: Int, p1: Int, p2: Int, bal: Int) : this((p0) + (p1 shl 2) + (p2 shl 4) + (bal shl 6))
    constructor(p0: Int, p1: Int, p2: Int, bal: Int, mask: Int, dir: Int) : this(
        p0,
        p1,
        p2,
        bal + dir * (p0.isFinal(mask) + p1.isFinal(mask shr 1) + p2.isFinal(mask shr 2)),
    )

    fun nextA() = DpState(p0.nextA(), p1.nextA(), p2.nextA(), bal, mask, -1)
    fun nextB() = DpState(p0.nextB(), p1.nextB(), p2.nextB(), bal, mask, 1)
    fun next(c: Char) = if (c == 'a') nextA() else nextB()

    companion object {
        private inline fun Int.isFinal(mask: Int) = if (this == 0 && ((mask and 1) == 1)) 1 else 0
    }
}

private fun verdict(p0: Int, p1: Int, p2: Int, c1: Char, c2: Char, bal: Int, mask: Int) : Int? {
    fun next(p: Int, bit: Int) : Pair<Int, Int> {
        if (p == 0) return 0 to 0
        val pp = p.next(c1)
        if (pp == 0) return 1 to ((if (c1 == 'a') -1 else 1) * (if (bit != 0) 1 else 0))
        val ppp = pp.next(c2)
        require(ppp == 0)
        return 2 to ((if (c2 == 'a') -1 else 1) * (if (bit != 0) 1 else 0))
    }
    val go = arrayOf(next(p0, mask and 1), next(p1, mask and 2), next(p2, mask and 4))
    //println(go.toList())
    val list = (0 until 4).runningFold(0 to 0) { acc, i ->  go[acc.first] }
    for (i in list.indices) {
        val first = list.indexOf(list[i])
        if (first != i) {
            val cycle = list.subList(first, i)
            return ((bal + cycle.sumOf { it.second }).sign + 1).takeIf { cycle.sumOf { 1 shl it.first } == mask }
        }
    }
    TODO()
}

@OptIn(ExperimentalTime::class)
private fun solve(s: String) : ModIntArray {
// 0 -a> 1
// 0 -b> 2
// 1 -a> 0
// 1 -b> 3
// 2 -a> 3
// 2 -b> 0
// 3 -a> 0
// 3 -b> 1
    //println("==== $s")
    val s0 = 0.next(s[0]).next(s[1])
    val s1 = 0.next(s[1])
    val s2 = 0
    val w1 = if (s0 == 0) {
        if (s[1] == 'a') -1 else 1
    } else 0
    val ans = ModIntArray(3) { ModInt(0) }

    for (mask_ in 1..7) {
        mask = mask_
        var states = buildMap {
            put(DpState(s0, s1, s2, w1 * (mask and 1)), ModInt(1))
        }
        //println(states)
        for (i in s.drop(2)) {
            //println("got $i")
            val newStates = mutableMapOf<DpState, ModInt>()
            fun add(k: DpState, v: ModInt) {
                newStates[k] = (newStates[k] ?: ModInt(0)) + v
            }
            if (i == 'a' || i == '?') {
                for ((k, v) in states.entries) {
                    add(k.nextA(), v)
                }
            }
            if (i == 'b' || i == '?') {
                for ((k, v) in states.entries) {
                    add(k.nextB(), v)
                }
            }
            states = newStates
        }
        //println(states.size)
        for ((p, count) in states) {
            verdict(p.p0, p.p1, p.p2, s[0], s[1], p.bal, mask)?.let {
                //println("($p0 $p1 $p2 $bal $mask) x $count goes to ${it}")
                ans[it] += count
            }
        }
    }
    return ans
}


@OptIn(ExperimentalTime::class)
fun main() {
    while (true) {
        val s = readlnOrNull() ?: break
        if (s[0] == '=') break
        if (s.length == 1) {
            when (s[0]) {
                'a' -> println("1 0 0")
                'b' -> println("0 0 1")
                '?' -> println("1 0 1")
            }
            continue
        }
        var ca = ModInt(0)
        var cb = ModInt(0)
        var cc = ModInt(0)
        for (c1 in 'a'..'b') {
            if (s[0] != c1 && s[0] != '?') continue
            for (c2 in 'a'..'b') {
                if (s[1] != c2 && s[1] != '?') continue
                //println(measureTime {
                    val (a, b, c) = solve("$c1$c2${s.drop(2)}")
                    ca += a
                    cb += b
                    cc += c
                //})
            }
        }
        println("${ca.x} ${cb.x} ${cc.x}")
        break
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }