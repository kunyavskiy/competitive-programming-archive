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

private fun solve(x: IntArray, q: IntArray) : List<ModInt> {
    val psum = x.map(ModInt::from).reduce(ModInt::plus) * ModInt(2)
    val psum2 = x.map(ModInt::from).map { it * it }.reduce(ModInt::plus)
    return List(q.size) {
        val mq = ModInt.from(q[it])
        psum2 + ModInt.from(x.size) * mq * mq - mq * psum
    }
}

private fun solve() {
    val pts = List(readInt()) { readInts().let { it[0] to it[1] }}
    val qs = List(readInt()) { readInts().let { it[0] to it[1] }}

    val a1 = solve(pts.map { it.first }.toIntArray(), qs.map { it.first }.toIntArray())
    val a2 = solve(pts.map { it.second }.toIntArray(), qs.map { it.second }.toIntArray())
    println(qs.indices.map { a1[it] + a2[it] }.reduce(ModInt::plus).x)
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