// markdownRenderer.js
import MarkdownIt from "markdown-it";
import markdownItKatex from "@vscode/markdown-it-katex";

const md = new MarkdownIt({
  html: true,
  linkify: true,
  typographer: true,
});

// Use markdown-it-katex for math rendering
// md.use(markdownItKatex, {
//   inlineMath: [['\\(', '\\)']],  // Custom inline math delimiter
//   blockMath: [['\\[', '\\]']]    // Custom block math delimiter
// });
md.use(markdownItKatex);


// Preprocess the content to handle \( and \)
const preprocess = (content) => {
  // Convert \( ... \) to $ ... $ and \[ ... \] to $ ... $
  return content

   // Convert \( ... \) to $...$
   .replace(/\\\((.+?)\\\)/g, (_, math) => `$${math.trim()}$`)
   // Convert \[ ... \] to $...$ (block math to inline math)
   .replace(/\\\[(.+?)\\\]/gs, (_, math) => `$$${math.trim()}$$`)
  //  // Remove extra spaces inside $ ... $
  //  .replace(/\$\s+(.+?)\s+\$/g, (_, math) => `$${math.trim()}$`);

   
    // .replace(/\\\((.+?)\\\)/g, "$$$1$$") // \( ... \) to $ ... $
    // .replace(/\\\[(.+?)\\\]/gs, "$$$1$$") // \[ ... \] to $ ... $

    // .replace(/\\\\\((.+?)\\\\\)/g, "$$$1$$") // \\( ... \\) to $ ... $
    // .replace(/\\\\\[(.+?)\\\\\]/g, "$$$1$$"); // \\[ ... \\] to $$ ... $$

};

export const render = (content) => {
  const preprocessedContent = preprocess(content);
  console.log(content);
  console.log(preprocessedContent);
  return md.render(preprocessedContent);
};

export default render;
