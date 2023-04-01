private fun solve() {
    var x = readInt()
    if (x % 2 == 0) {
        println(-1)
        return
    }
    val ans = buildList {
        while (x != 1) {
            if (x % 4 == 1) {
                add(1)
                x = (x + 1) / 2
            } else {
                add(2)
                x = (x - 1) / 2
            }
        }
        reverse()
    }
    println(ans.size)
    println(ans.joinToString(" "))
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