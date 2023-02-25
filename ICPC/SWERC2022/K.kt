private fun solve() {
    val (n, m) = readInts()
    val es = List(m) { readInts().map { it - 1 } }
    val degs = IntArray(n)
    for ((u, v) in es) {
        degs[u]++
        degs[v]++
    }
    val id = degs.indices.minByOrNull { degs[it] }!!
    if (degs[id] != n - 1) {
        require(es.any { it[0] != id && it[1] != id })
        println(2)
        println(es.joinToString(" ") {
            if (it[0] == id || it[1] == id) {
                "1"
            } else {
                "2"
            }
        })
    } else {
        println(3)
        println(es.joinToString(" ") {
           when {
               it.contains(0) && it.contains(1) -> "3"
               it.contains(0) -> "1"
               it.contains(1) -> "2"
               else -> "3"
           }
        })
    }
}

fun main() {
    repeat(readInt()) {
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }