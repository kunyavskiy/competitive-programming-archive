private const val MOD = 1000000007

private fun solve() {
    val n = readInt()
    println(
        readLn().asSequence().withIndex().filter { it.value != 'F' }
            .zipWithNext().filter { it.first.value != it.second.value }
            .sumOf { (it.first.index + 1).toLong() * (n - it.second.index) } % MOD
    )
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