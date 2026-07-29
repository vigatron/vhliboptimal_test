import os

def merge_markdown_files():
    output_filename = "results.md"

    # Получаем все файлы в текущей папке с расширением .md, кроме самого файла результата
    md_files = [
        f for f in os.listdir('.')
        if f.endswith('.md') and f != output_filename and os.path.isfile(f)
    ]

    # Сортируем файлы по алфавиту, чтобы порядок объединения был предсказуемым
    md_files.sort()

    if not md_files:
        print("Файлы .md для объединения не найдены.")
        return

    # Открываем итоговый файл для записи (кодировка utf-8 для корректной работы с кириллицей)
    with open(output_filename, "w", encoding="utf-8") as outfile:
        for index, file_name in enumerate(md_files):
            try:
                with open(file_name, "r", encoding="utf-8") as infile:
                    content = infile.read()

                    # Записываем содержимое текущего файла
                    outfile.write(content)

                    # Если это не последний файл, добавляем пустую строку для разделения.
                    # Также проверяем, заканчивается ли файл уже на перенос строки,
                    # чтобы не плодить лишние отступы.
                    if index < len(md_files) - 1:
                        if not content.endswith('\n'):
                            outfile.write('\n')
                        outfile.write('\n')

                print(f"Успешно добавлен: {file_name}")
            except Exception as e:
                print(f"Ошибка при чтении файла {file_name}: {e}")

    print(f"\nВсе файлы успешно объединены в {output_filename}")

if __name__ == "__main__":
    merge_markdown_files()
