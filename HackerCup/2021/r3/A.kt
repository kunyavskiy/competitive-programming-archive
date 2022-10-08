/*private class Dsu(n: Int) {
    private val p = IntArray(n) { it }
    private val size = IntArray(n) { 1 }
    private val right = IntArray(n) { it }

    operator fun get(x: Int): Int {
        return (if (x != p[x]) get(p[x]) else x)
            .also { p[x] = it }
    }

    fun merge(x: Int, y: Int) {
        val xx = get(x)
        val yy = get(y)
        if (xx != yy) {
            val nroot = if (size[xx] > size[yy]) xx else yy
            val other = xx xor yy xor nroot
            p[other] = nroot
            size[nroot] = size[xx] + size[yy]
            right[nroot] = maxOf(right[xx], right[yy])
        }
    }

    fun getSize(x: Int) = size[get(x)]
    fun getRight(x: Int) = right[get(x)]
}

private const val MOD = 1_000_000_007

private fun solve() {
    val (n, m) = readInts()
    val d = Dsu(n)
    var ans = n.toLong() * (n - 1) / 2
    var res = 1L
    repeat(m) {
        val (a, b) = readInts().map { it - 1 }.sorted()

        while (d[a] != d[b]) {
            val na = d.getRight(a) + 1
            val s1 = d.getSize(a)
            val s2 = d.getSize(na)
            ans += s1.toLong() * s2
            d.merge(a, na)
        }

        res = (res * (ans % MOD)) % MOD
    }
    println(res)
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
 */