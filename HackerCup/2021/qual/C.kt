private fun solve() {
    val (n, k_) = readInts()
    val k = 2 * k_
    val g = Array(n) { mutableListOf<Int>() }
    val c = readInts()
    repeat(n - 1) {
        val (a, b) = readInts()
        g[a - 1].add(b - 1)
        g[b - 1].add(a - 1)
    }

    fun maxOf(a: Int?, b: Int?) = maxOf<Int>(a ?: Int.MIN_VALUE, b ?: Int.MIN_VALUE)

    fun calc(v: Int, p: Int): IntArray {
        val sons = g[v].filter { it != p }.map { calc(it, v) }
        val odd = IntArray(k + 1) { Int.MIN_VALUE / 2 }
        val even = IntArray(k + 1) { Int.MIN_VALUE / 2 }
        even[0] = c[v]
        for (son in sons) {
            val nodd = IntArray(k + 1) { a -> maxOf(odd[a], (1..a).maxOfOrNull { even[a - it] + son[it] }) }
            val neven = IntArray(k + 1) { a -> maxOf(even[a], (1..a).maxOfOrNull { odd[a - it] + son[it] }) }
            nodd.copyInto(odd)
            neven.copyInto(even)
        }
        val oshift = if (v == 0) 1 else 0
        val eshift = if (v != 0) 1 else 0
        return IntArray(k + 1) {
            maxOf(odd.getOrNull(it - oshift), even.getOrNull(it - eshift))
        }.also { println("v = $v, out = ${it.joinToString()}") }
    }
    println(calc(0, -1).maxOrNull()!!)
}

fun main() {
    repeat (readInt()) {
        print("Case #${it+1}: ")
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }