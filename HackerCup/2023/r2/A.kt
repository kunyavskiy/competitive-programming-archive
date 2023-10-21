private fun solve() {
    val (r, c) = readInts()
    val s = List(r) { readln() }
    val used = List(r) { BooleanArray(c) { false } }
    var count = 0
    fun dfs (r: Int, c:Int, to: MutableList<Pair<Int, Int>>) {
        when (s.getOrNull(r)?.getOrNull(c)) {
            null, 'B' -> {}
            'W' -> {
                if (!used[r][c]) {
                    count++
                    used[r][c] = true
                    dfs(r - 1, c, to)
                    dfs(r + 1, c, to)
                    dfs(r, c - 1, to)
                    dfs(r, c + 1, to)
                }
            }

            '.' -> {
                to.add(r to c)
            }

            else -> TODO()
        }
    }

    val ans = List(r) { IntArray(c) }

    for (i in s.indices) {
        for (j in s[i].indices) {
            if (s[i][j] == 'W' && !used[i][j]) {
                val l = mutableListOf<Pair<Int, Int>>()
                count = 0
                dfs(i, j, l)
                l.distinct().singleOrNull()?.let { (x, y) ->
                    ans[x][y] += count
                }
            }
        }
    }
    val res = ans.maxOf { it.max() }
    println(res)
//    if (res != 0) {
//        println("YES")
//    } else {
//        println("NO")
//    }
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }