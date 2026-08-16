document.addEventListener('DOMContentLoaded', () => {
    // Theme Switcher Logic
    const themeBtn = document.getElementById('theme-btn');
    let currentTheme = 'light';
    try {
        currentTheme = localStorage.getItem('theme') || 'light';
    } catch(e) {}
    
    document.documentElement.setAttribute('data-theme', currentTheme);
    document.body.setAttribute('data-theme', currentTheme);
    if (themeBtn) {
        themeBtn.innerText = currentTheme === 'dark' ? '☀️' : '🌙';
        
        themeBtn.addEventListener('click', () => {
            let theme = document.documentElement.getAttribute('data-theme');
            let newTheme = theme === 'dark' ? 'light' : 'dark';
            document.documentElement.setAttribute('data-theme', newTheme);
            document.body.setAttribute('data-theme', newTheme);
            try {
                localStorage.setItem('theme', newTheme);
            } catch(e) {}
            themeBtn.innerText = newTheme === 'dark' ? '☀️' : '🌙';
        });
    }

    // Sidebar Mobile Toggle
    const toggleBtn = document.getElementById('sidebar-toggle');
    const sidebar = document.querySelector('.sidebar');
    if (toggleBtn && sidebar) {
        toggleBtn.addEventListener('click', () => {
            if (sidebar.style.display === 'flex') {
                sidebar.style.display = 'none';
            } else {
                sidebar.style.display = 'flex';
            }
        });
    }
});
