private fun solve() {
    readInt()
    val s = readln().map { it == '1' }.toBooleanArray()
    val used = BooleanArray(s.size)
    for (i in 1 .. s.size) {
        if (s[i-1]) {
            used[i-1] = true
            for (j in i .. s.size step i) {
                s[j - 1] = !s[j - 1]
            }
        }
    }
    var tot = used.count { it }
    val ans = List(readInt()) {
        val x = readInt() - 1
        tot += if (used[x]) {
            used[x] = false
            -1
        } else {
            used[x] = true
            1
        }
        tot
    }
    //println(ans.last())
    println(ans.map { it.toLong() }.sum())
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