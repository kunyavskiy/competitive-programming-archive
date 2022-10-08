private fun c3(x: Long) = x * (x - 1) * (x - 2) / 6
private fun c2(x: Long) = x * (x - 1) / 2
private fun solve() {
    val n = readInt()
    val next = mutableListOf(IntArray(26) { -1 })
    val count = mutableListOf(0)
    repeat(n) {
        count[0]++
        val m = readInt()
        val map = IntArray(m)
        map[0] = 0
        for (node in 1 until m) {
            val (pp, cc) = readStrings()
            val p = pp.toInt() - 1
            val c = cc[0].code - 'a'.code
            if (next[map[p]][c] == -1) {
                next[map[p]][c] = next.size
                next.add(IntArray(26) { -1 })
                count.add(0)
            }
            map[node] = next[map[p]][c]
            count[map[node]]++
        }
    }
    println(
        count.sumOf {
            c3(it.toLong()) + c2(it.toLong()) * (n - it) + it * c2((n - it).toLong())
        }
    )
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