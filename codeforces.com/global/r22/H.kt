private const val P1 = 239
private const val P2 = 241
private const val MOD1 = 1000000007
private const val MOD2 = 1000000009

private inline fun addMod(a:Int, b:Int, mod:Int) : Int {
    val c = a + b
    return if (c >= mod) c - mod else c
}

private inline fun subMod(a:Int, b:Int, mod:Int) : Int {
    val c = a - b
    return if (c < 0) c + mod else c
}

@JvmInline
value class EncodedLong(val x: Long) {
    val f get() = (x and ((1L shl 32) -1 )).toInt()
    val s get() = (x shr 32).toInt()
    constructor(a: Int, b: Int) : this((a.toLong() shl 32) or b.toLong())

    operator fun plus(other: EncodedLong) = EncodedLong(addMod(f, other.f, MOD1), addMod(s, other.s, MOD2))
    operator fun minus(other: EncodedLong) = EncodedLong(subMod(f, other.f, MOD1), subMod(s, other.s, MOD2))
    operator fun times(other: EncodedLong) = EncodedLong((f.toLong() * other.f.toLong() % MOD1).toInt(), (s.toLong() * other.s.toLong() % MOD2).toInt())
}

@JvmInline
private value class EncodedLongArray(private val storage:LongArray) {
    operator fun get(index: Int) = EncodedLong(storage[index])
    operator fun set(index: Int, value: EncodedLong) { storage[index] = value.x }
    val size get() = storage.size
}
private inline fun EncodedLongArray(n: Int, init: (Int) -> EncodedLong) = EncodedLongArray(LongArray(n) { init(it).x })


private class Hasher(x: IntArray) {
    val P = EncodedLong(P1, P2)
    private val degs = EncodedLongArray(x.size + 1) { EncodedLong(1, 1) }.apply {
        for (i in 1 until x.size) {
            set(i, get(i - 1) * P)
        }
    }
    val a = EncodedLongArray(x.size + 1) { EncodedLong(0) }.apply {
        for (i in 0 until x.size) {
            set(i + 1, get(i) * P + EncodedLong(x[i], x[i]))
        }
    }

    fun hash(l: Int, r: Int) = (a[r] - a[l] * degs[r - l]).x
}

private class ReversedHasher(x: IntArray) {
    val n = x.size
    val delegate = Hasher(x.reversedArray())
    fun hash(l:Int, r:Int) = delegate.hash(n - r - 1, n - l - 1)
}

@OptIn(ExperimentalStdlibApi::class)
fun main() {
    val ops = List(readInt()) {
        val s = readStrings()
        if (s[0] == "pop")
            -1
        else
            s[1][0].code
    }
    val data = ops.filter { it != -1 }.toIntArray()
    val h = Hasher(data)
    val rh = ReversedHasher(data)

    fun isPalin(l:Int, r:Int) = h.hash(l, r) == rh.hash(l, r)

    val ans = IntArray(ops.size)



    run {
        var l = 0
        var r = 0
        var cur = 0
        val s = mutableMapOf<Long, Int>()
        val best = IntArray(data.size)
        val bigSuffix = IntArray(data.size)
        for (i in ops) {
            if (ops[i] == -1) {
                l++
            } else {
                cur += 2
                r++
                while (cur > 1 && !isPalin(r - cur, r)) cur -= 2
                val hh = h.hash(r - cur, r)
                s.put(hh, s.getOrDefault(hh, 0) + 1)
            }
            add(s.size)
        }
    }
    println(ans.joinToString("\n"))
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
