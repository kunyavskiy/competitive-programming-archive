private fun solve() {
    val (r, c) = readInts()
    val a = List(r) { readLn() }
    val b = List(r) { x -> BooleanArray(c) { y -> a[x][y] != '#' } }
    val dir = listOf(-1 to 0, 1 to 0, 0 to -1, 0 to 1)

    tailrec fun check(x: Int, y: Int) {
        val goodDir = dir.filter { (dx, dy) ->
            b.getOrNull(x + dx)?.getOrNull(y + dy) == true
        }
        if (goodDir.size >= 2) return
        b[x][y] = false
        if (goodDir.size == 1) {
            val (dx, dy) = goodDir[0]
            check(x + dx, y + dy)
        }
    }
    for (x in b.indices) {
        for (y in b[x].indices) {
            if (b[x][y]) {
                check(x, y)
            }
        }
    }
    for (x in b.indices) {
        for (y in b[x].indices) {
            if (!b[x][y] && a[x][y] == '^') {
                println("Impossible")
                return
            }
        }
    }
    println("Possible")
    println(a.indices.joinToString("\n") { x ->
        b[x].indices.joinToString("") { y ->
            if (b[x][y]) "^" else a[x][y].toString()
        }
    })
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