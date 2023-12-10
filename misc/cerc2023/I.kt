private fun query(l: List<Int>) : List<Int> {
    if (l.all { it == 0 }) return List(l.size) { 0 }
    println("QUERY ${l.joinToString("")}")
    System.out.flush()
    return readInts()
}
fun main() {
    val n = readInt()
    val deg = query(List(n) { 1 }).toIntArray()
    val x = IntArray(n)
    for (i in 0 until 15) {
        val d = query(List(n) { if ((it and (1 shl i) != 0)) 1 else 0 })
        for (j in d.indices) {
            if (d[j] % 2 == 1) {
                x[j] = x[j] or (1 shl i)
            }
        }
    }
    val q = deg.indices.filterTo(mutableListOf()) { deg[it] == 1 }
    val ans = mutableListOf<Pair<Int, Int>>()
    val used = BooleanArray(n)
    while (ans.size < n - 1) {
        val v = q[ans.size]
        used[v] = true
        val p = x[v]
        require(!used[p])
        ans.add(v to p)
        x[p] = x[p] xor v
        deg[p]--
        if (deg[p] == 1) {
            q.add(p)
        }
    }
    println("ANSWER")
    println(ans.joinToString("\n") { "${it.first + 1} ${it.second + 1}" })
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }