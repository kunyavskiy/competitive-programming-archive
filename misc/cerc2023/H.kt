fun main() {
    val s = readln()
    if (s == "ENCODE") {
         var first: String? = null
        val data = buildMap {
            while (true) {
                val x = readlnOrNull() ?: break
                val (manager, others) = x.split(":")
                if (first == null) {
                    first = manager
                }
                val l = others.split(" ").filter { it.isNotEmpty() }
                put(manager, l)
            }
        }
        val order = mutableListOf<String>()
        val bits = mutableListOf<Int>()
        fun dfs(name: String) {
            order.add(name)
            for (i in data[name] ?: emptyList()) {
                bits.add(1)
                dfs(i)
            }
            bits.add(0)
        }
        dfs(first!!)
        println(order.joinToString("\n"))
        println(bits.joinToString(""))
    } else {
        val bits: String
        val names = buildList {
            while (true) {
                val x = readlnOrNull() ?: break
                add(x)
            }
            bits = last()
            removeAt(lastIndex)
        }
        val data = mutableMapOf<String, MutableList<String>>()
        val stack = mutableListOf<String>(names[0])
        var ptr = 1
        for (b in bits) {
            if (b == '1') {
                data.getOrPut(stack.last()) { mutableListOf() }.add(names[ptr])
                stack.add(names[ptr])
                ptr++
            } else {
                stack.removeAt(stack.lastIndex)
            }
        }
        fun dfs(name: String) {
            data[name]?.let {
                println("$name: ${it.joinToString(" ")}")
                for (i in it) {
                    dfs(i)
                }
            }
        }
        dfs(names[0])
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }