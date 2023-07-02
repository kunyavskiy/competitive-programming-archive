private fun solve() {
    val (r, c) = readInts()
    val s = List(r) { readLn() }
    val starts = buildList {
        for (i in s.indices) {
            for (j in s[i].indices) {
                if (s[i][j].isLowerCase()) {
                    add(i to j)
                }
            }
        }
    }
    val ends = buildList {
        for (i in s.indices) {
            for (j in s[i].indices) {
                if (s[i][j].isUpperCase()) {
                    add(i to j)
                }
            }
        }
    }
    val dirs = listOf(
            0 to 1,
            1 to 0,
            0 to -1,
            -1 to 0,
    )
    val ans = mutableListOf<String>()
    for ((sx, sy) in ends) {
        val reachable = Array(r) { BooleanArray(c) }
        reachable[sx][sy] = true
        for (i in 0 until r) {
            for (j in 0 until c) {
                if (s[i][j] == '#') {
                    reachable[i][j] = true
                }
            }
        }
        val q = mutableListOf(sx to sy)
        var i = 0
        while (i < q.size) {
            fun isReachable(x: Int, y: Int) = reachable.getOrNull(x)?.getOrNull(y) ?: true
            fun isStar(x: Int, y: Int) = s.getOrNull(x)?.getOrNull(y) == '*'
            val (x, y) = q[i++]
            for ((dx, dy) in dirs) {
                var c = 1
                while (true) {
                    when {
                        isReachable(x + c * dx, y + c * dy) -> {
                            for (dst in 1 until c) {
                                q.add(x + dst * dx to y + dst * dy)
                                reachable[x + dst * dx][y + dst * dy] = true
                            }
                            break
                        }

                        isStar(x + c * dx, y + c * dy) -> break
                    }
                    c++
                }
            }
        }
        for ((x, y) in starts) {
            if (reachable[x][y]) {
                ans.add("${s[x][y]}${s[sx][sy]}")
            }
        }
    }
    if (ans.isEmpty()) {
        ans.add("NONE")
    }
    println(ans.sorted().joinToString(" "))
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