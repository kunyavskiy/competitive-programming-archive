private const val MOD = 1000000007

@JvmInline
private value class ModInt(val x: Int) {
    operator fun plus(other: ModInt) = ModInt((x + other.x).let { if (it >= MOD) it - MOD else it })
    operator fun minus(other: ModInt) = ModInt((x - other.x).let { if (it < 0) it + MOD else it })
    operator fun times(other: ModInt) = ModInt((x.toLong() * other.x % MOD).toInt())
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

    operator fun div(other: ModInt) = this * other.power(MOD - 2)

    companion object {
        fun from(x: Int) = ModInt((x % MOD + MOD) % MOD)
        fun from(x: Long) = ModInt(((x % MOD).toInt() + MOD) % MOD)
    }
}

@JvmInline
private value class ModIntArray(private val storage:IntArray) {
    operator fun get(index: Int) = ModInt(storage[index])
    operator fun set(index: Int, value: ModInt) { storage[index] = value.x }
    val size get() = storage.size
}
private inline fun ModIntArray(n: Int, init: (Int) -> ModInt) = ModIntArray(IntArray(n) { init(it).x })

private const val MAX = 3000 * 3000 + 10
private val fs = ModIntArray(MAX) { ModInt.from(0) }
private val ifs = ModIntArray(MAX) { ModInt.from(0) }

private fun solve() {
    val (n, k) = readInts()
    val inp = List(n) { readInts() }
    val c = inp.map { it[0] }.toIntArray()
    val w = inp.map { it[1] }.toIntArray()

    val totLess = c.indices.filter { w[it] < w[0] }.sumOf { c[it] }
    val totSame = c.indices.filter { w[it] == w[0] }.sumOf { c[it] }
    val totMore = c.indices.filter { w[it] > w[0] }.sumOf { c[it] }
    val tot = totLess + totSame + totMore

    fun count(c:Int) = when {
        c <= k -> ModInt.from(0)
        else -> fs[c] / fs[c - k - 1]
    }

//    println("cf = ${ModInt.from(c[0]) / ModInt.from(totSame)}, a = ${count(totLess + totSame)}, b = ${count(totLess)}, c = ${count(tot)}")

    val ans = ModInt.from(c[0]) / ModInt.from(totSame) * (count(totLess + totSame) - count(totLess)) / count(tot)
    println(ans.x)
}

fun main() {
    fs[0] = ModInt.from(1)
    ifs[0] = fs[0]
    for (i in 1 until fs.size) {
        fs[i] = fs[i-1] * ModInt.from(i)
        ifs[i] = ModInt.from(1) / fs[i]
    }
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